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

#include "ValueWrapper.h"
#include "IBeanWrapper.h"
#include "LocalLibrary.h"
#include "AutumnException.h"

string IBeanWrapper::getConArgTypes(void** pPrams, int num)
{
	string types;
	void* pDummy;

	int rtn = operateCreator(pPrams, num, opGetConArgType, types, pDummy);
	if( rtn )
		throw new MissDefinitionEx("IBeanWrapper", 
				"getConArgTypes", 
				"Getting bean[" + this->BeanName + "] constructor-arg types failed!");

	return types;
}

void* IBeanWrapper::createBean(void** pPrams, int num)
{
	string sDummy;
	void* pBean;

	int rtn = operateCreator(pPrams, num, opCreateBean, sDummy, pBean);
	if( rtn )
		throw new MissDefinitionEx("IBeanWrapper", 
				"createBean(void**, int)", 
				"Creating bean[" + this->BeanName + "] failed!");

	return pBean;
}

void IBeanWrapper::deleteBean()
{
	throw new MissDefinitionEx("IBeanWrapper", 
		"deleteBean()", 
		"Definition of bean[" + this->BeanName + "] deleteBean() method is missing!");
}

void IBeanWrapper::initializeBean()
{
	throw new MissDefinitionEx("IBeanWrapper", 
			"initializeBean", 
			"Definition of bean[" + this->BeanName + "] initializeBean method is missing!");
}

void IBeanWrapper::destroyBean()
{
	throw new MissDefinitionEx("IBeanWrapper", 
			"destoryBean", 
			"Definition of bean[" + this->BeanName + "] destoryBean method is missing!");
}

int IBeanWrapper::operateBeanProperty(const char* name, const char* op, string& type, void* value)
{
	throw new MissDefinitionEx("IBeanWrapper", 
			"operateBeanProperty", 
			"Definition of bean[" + this->BeanName + "] set/get " +
				name + " method is missing!");
	//avoid warning for some compiler
	return -1;
}

int IBeanWrapper::operateCreator(void** p, int num, const char* op, string& args, void*& pr)
{
	throw new MissDefinitionEx("IBeanWrapper", "operateCreator", 
			"Definition of bean[" + this->BeanName + 
			"] create/gettype method is missing!");
	//avoid warning for some compiler
	return -1;
}

/** 
 * Destructor
 */
IBeanWrapper::~IBeanWrapper()
{
	AutumnLog::getInstance()->debug("IBeanWrapper->~IBeanWrapper ");
	
	for(int i=0; i<this->Parameters.size(); i++)
		delete (ValueWrapper*)this->Parameters[i];

	AutumnLog::getInstance()->debug("IBeanWrapper->~IBeanWrapper return");
}

/** register local function for local library */
void registerLocalFunction(const char* name, void* f)
{
	LocalLibrary::getInstance()->addFunction(name, f);
}

