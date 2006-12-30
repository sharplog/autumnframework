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
#include "AutumnException.h"

/** 
 * Wrapper of bean
 * 
 * @version 0.1.0
 * @since 2006-12-23
 */

void* IBeanWrapper::createBean()
{
	throw new MissDefinitionEx("IBeanWrapper", 
			"createBean", 
			"Definition of bean[" + this->BeanName + "] createBean method is missing!");
	//avoid warning for some compiler
	return NULL;
}

void* IBeanWrapper::createBean(void** pPrams, int num)
{
	throw new MissDefinitionEx("IBeanWrapper", 
			"createBean(void**, int)", 
			"Definition of bean[" + this->BeanName + "] createBean(void**, int) method is missing!");
	//avoid warning for some compiler
	return NULL;
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

int IBeanWrapper::setBeanProperty(const char* name, const char* type, void* value)
{
	throw new MissDefinitionEx("IBeanWrapper", 
			"setBean", 
			"Definition of bean[" + this->BeanName + "] set" +
				name + "(" + type + ") method is missing!");
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
}

