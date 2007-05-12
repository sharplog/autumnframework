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

string IBeanWrapper::getConArgTypes(string& ConMethod, int num)
{
	string types;

	int rtn = this->getParamTypes(ConMethod, types, num);
	if( rtn )
		throw new MissDefinitionEx("IBeanWrapper", 
				"getConArgTypes", 
				"Getting bean[" + this->BeanName + "] constructor-arg types failed!");

	return types;
}

bool IBeanWrapper::deleteBean()
{
	if( this->getBean() == NULL )
		return true;
	
	string method = this->getDestroyMethod();
	if( !method.empty() ){
		if( this->execVoidMethod(method, NULL, 0) < 0 ) {
			throw new MissDefinitionEx("IBeanWrapper", 
					"deleteBean", 
					"Executing destory-method [" + method + "] of bean [" + 
					this->BeanName + "] failed!");
		}
	}
	
	method = this->getDeleteMethod();
	if( !method.empty() ) {
		void* p = this->getBean();
		if( this->execVoidMethod(method, &p, 1) < 0 ) {
			throw new MissDefinitionEx("IBeanWrapper", 
					"deleteBean", 
					"Executing delete-method [" + method + "] of bean [" + 
					this->BeanName + "] failed!");
		}
		return true;
	}
	else
		return false;
}

/** 
 * Destructor
 */
IBeanWrapper::~IBeanWrapper()
{
	AutumnLog::getInstance()->debug("IBeanWrapper->~IBeanWrapper [" + 
			this->getBeanName() + "]");
	
	for(int i=0; i<this->Parameters.size(); i++)
		delete (ValueWrapper*)this->Parameters[i];

	AutumnLog::getInstance()->debug("IBeanWrapper->~IBeanWrapper return");
}

/** register local function for local library */
void registerLocalFunction(const char* name, void* f)
{
	LocalLibrary::getInstance()->addFunction(name, f);
}

