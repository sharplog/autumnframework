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

#include <string>
#include "TypeManager.h"
#include "ValueWrapper.h"
#include "AutumnLog.h"

using namespace std;

/**
 * Argument value for constuctor or setter functions.
 * 
 * @version 0.1.0
 * @since 2006-11-24
 */

ValueWrapper::ValueWrapper(string type, StrValueList& vl, bool managed):
  Type(type), Managed(managed){
	this->PointerOfValue = TypeManager::getInstance()->
		createValue(vl, type);
}
	
ValueWrapper::~ValueWrapper(){
	if( this->PointerOfValue != NULL ){
		AutumnLog::getInstance()->debug("ValueWrapper->~ValueWrapper, type: " + this->Type);
		if( this->Managed ){
			TypeManager::getInstance()->
				freeValue(this->PointerOfValue, this->Type);
		}
		else{
			TypeManager::getInstance()->
				freeSelfSpace(this->PointerOfValue, this->Type);
		}
	}
}
