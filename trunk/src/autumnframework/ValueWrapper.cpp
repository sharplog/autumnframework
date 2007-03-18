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
#include "IAutumnType.h"
#include "ValueWrapper.h"
#include "AutumnLog.h"

using namespace std;

ValueWrapper::ValueWrapper(string type, StrValueList& vl, bool managed, IAutumnType* at):
  Type(type), Managed(managed), TypeBean(at){
	StrIterator it = vl.begin();
	this->PointerOfValue = this->TypeBean->createValue(type, vl, it);
}
	
ValueWrapper::~ValueWrapper(){
	if( this->PointerOfValue != NULL ){
		AutumnLog::getInstance()->debug("ValueWrapper->~ValueWrapper, type: " + this->Type);
		if( this->Managed ){
			this->TypeBean->freeValue(this->PointerOfValue, this->Type);
		}
		else{
			this->TypeBean->freeSelfSpace(this->PointerOfValue);
		}
	}
}
