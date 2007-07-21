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

#include <memory>
#include "BeanConfig.h"
#include "IBeanWrapper.h"
#include "AutumnException.h"

namespace Autumn{

/** erase space char */
string trimString(const string v)
{
	string s=v;
	for(int i=0; i<s.size(); ){
		if( isspace(s[i]) ){
			s.erase(i,1);
		}
		else i++;
	}
	return s;
}


BeanConfig::BeanConfig(TBean& beandef, WrapperMaker* wc, WrapperFreer* wd)
{
	this->Name = beandef.Name;
	this->WrapperCreater = wc;
	this->WrapperDeleter = wd;
	this->DependedObjects = beandef.DependedObjects;
	this->Singleton = beandef.Singleton;
	this->FactoryBean = beandef.FactoryBean;
	this->ConMethod = beandef.ConMethod;
	this->InitMethod = beandef.InitMethod;
	this->DestroyMethod = beandef.DestroyMethod;
	this->DeleteMethod = beandef.DeleteMethod;
	this->GotArgTypes = false;
	this->ConArgs = new PropertyList;
	this->Properties = new PropertyList;
	
	int i;
	TProperty *p;
	
	for(i=0; i<beandef.ConArgs.size(); i++){
		p = &beandef.ConArgs[i];
		this->ConArgs->push_back(new BeanProperty(p->Name,
			trimString(p->Type),
			p->Value, p->IsBeanRef, p->Managed));
	}
	
	// the following depends on BeanWrapperMacro implementation.
	auto_ptr<IBeanWrapper> pw( wc() );
	for(i=0; i<beandef.Properties.size(); i++){
		p = &beandef.Properties[i];

		string tmpType = p->Type;
		if( tmpType.empty() )
			pw->getBeanPropertyType(p->Name.c_str(), tmpType);

		this->Properties->push_back(new BeanProperty(p->Name, 
				trimString(tmpType), 
				p->Value, p->IsBeanRef, p->Managed));
	}
}

BeanConfig::~BeanConfig()
{
	int i;
	for(i=0; i<this->ConArgs->size(); i++){
		delete (*this->ConArgs)[i];
	}
	for(i=0; i<this->Properties->size(); i++){
		delete (*this->Properties)[i];
	}
	delete this->ConArgs;
	delete this->Properties;	
}

IBeanWrapper* BeanConfig::createWrapper()
{
	IBeanWrapper* p = this->WrapperCreater();
	p->setWrapperDeleter(this->WrapperDeleter);
		
	p->setSingleton( this->Singleton );
	p->setInitMethod( this->InitMethod );
	p->setDestroyMethod( this->DestroyMethod );
	p->setDeleteMethod( this->DeleteMethod );

	return p;
}

PropertyList* BeanConfig::getConArgs(IBeanWrapper* pw) {
	int argNum = this->ConArgs->size();

	if( !this->GotArgTypes && argNum > 0 ){
		string conMethod = this->getConMethod();
		string ConArgTypes = pw->getConArgTypes(conMethod, argNum);
		
		string tmpType;
		int start, end = -1;
		for(int i=0; i<this->ConArgs->size(); i++){
			start = end + 1;
			end = ConArgTypes.find(typeSeparator, start);
			if( end == string::npos ){
				throw MissDefinitionEx("BeanConfig", "getConArgs", 
					"the ConArgs' types are less than arguments!");
			}
			tmpType = ConArgTypes.substr(start, end - start);
			
			(*this->ConArgs)[i]->setType(trimString(tmpType));
		}
		
		this->GotArgTypes = true;
	}
	return this->ConArgs;
}

} // End namespace Autumn

