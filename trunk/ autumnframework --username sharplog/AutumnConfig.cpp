/*
* Copyright 2006 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "AutumnDefinition.h"
#include "AutumnException.h"
#include "IBasicType.h"
#include "ICombinedType.h"
#include "IBeanWrapper.h"
#include "ILibrary.h"
#include "ObjectType.h"
#include "LocalLibrary.h"
#include "DynamicLibrary.h"
#include "TypeManager.h"
#include "AutumnConfig.h"

/**
 * AutumnFramework's configuration
 * 
 * @version 0.1.0
 * @since 2006-12-16
 */

AutumnConfig::AutumnConfig(IResource* config)
{
	const vector<TLibrary*> *pLibs = config->getLibraries();
	for(int i=0; i<pLibs->size(); i++){
		this->processLibrary(*pLibs->at(i));
	}

}

void AutumnConfig::processLibrary(TLibrary& lib)
{
	ILibrary* pl;

	if( lib.Path != LocalLibraryPath){
		pl = new DynamicLibrary(lib.Name, lib.Path);
		this->Libs.push_back(pl);
	}
	else{
		pl = LocalLibrary::getInstance();
	}
	
	int i;
	for(i=0; i<lib.Beans.size(); i++){
		this->processBean(lib.Beans.at(i), pl);
	}

	for(i=0; i<lib.Types.size(); i++){
		this->processType(lib.Types.at(i), pl);
	}
}

/** Deal with each bean */
void AutumnConfig::processBean(TBean& bean, ILibrary* pl)
{
	// the bean exists or not
	if( this->Beans.find(bean.Name) != this->Beans.end() ){
		throw new ReduplicateEx("AutumnConfig", "processBean", 
			"Reduplicate defined bean [" + bean.Name + "]!");
	}

	// get bean wrapper maker function
	string funName = this->mangleName("bean", "create", bean.ClassName);
	WrapperMaker* pw = (WrapperMaker*)pl->getFunction(funName);
	if( pw == NULL ){
		throw new NotFoundEx("AutumnConfig", "processBean", 
			"Geting WrapperMaker failed for class '" + bean.ClassName + "'.");
	}

	// get bean wrapper freer function
	funName = this->mangleName("bean", "delete", bean.ClassName);
	WrapperFreer* pd = (WrapperFreer*)pl->getFunction(funName);
	if( pd == NULL ){
		throw new NotFoundEx("AutumnConfig", "processBean", 
			"Geting WrapperFreer failed for class '" + bean.ClassName + "'.");
	}
	
	// create BeanConfig
	auto_ptr<BeanConfig> pb(new BeanConfig(bean, pw, pd));
	this->Beans.insert(make_pair(bean.Name, pb.release()));

	//Every class as a basic type of data
	TypeManager::getInstance()->setBasicType(bean.ClassName, new ObjectType);
}

/** Deal with each type */
void AutumnConfig::processType(TType& type, ILibrary* pl)
{
	string funName = this->mangleName("type", "create", type.ClassName);

	if( type.IsBasic ){
		typedef IBasicType* bfunType();
		bfunType* fb = (bfunType*)pl->getFunction(funName);
		IBasicType* pb = fb();
		TypeManager::getInstance()->setBasicType(type.Name, pb);
	}
	else{
		typedef ICombinedType* cfunType();
		cfunType* fc = (cfunType*)pl->getFunction(funName);
		ICombinedType* pc = fc();
		TypeManager::getInstance()->setCombinedType(type.Name, pc);
	}
}

string AutumnConfig::mangleName(string objType, string  op, string objName)
{
	if( objType == "bean" ){
		if( op == "create" )
			return "create_" + objName + "_Wrapper";
		else if( op == "delete" )
			return "delete_" + objName + "_Wrapper";
	}
	else if( objType == "type" ){
		if( op == "create" )
			return "create_" + objName + "_Type";
	}
	throw new NotFoundEx("AutumnConfig", "mangleName", 
		"type[" + objType + "]->operation[" + op +"] is not found!");
}

AutumnConfig::~AutumnConfig()
{
	for(int i=0; i<this->Libs.size(); i++)
		delete this->Libs.at(i);

	for(map<string, BeanConfig*>::iterator it=this->Beans.begin();
			it!=this->Beans.end(); it++)
		delete it->second;
}

BeanConfig* AutumnConfig::getBeanConfig(string name)
{
	map<string, BeanConfig*>::iterator it = this->Beans.find(name);
	if( it != this->Beans.end() )
		return it->second;
	else
		return NULL;
}
