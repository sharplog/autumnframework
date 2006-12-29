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
#include "BeanProperty.h"
#include "AutumnException.h"

/** 
 * Set a object's property.
 * @param pw The object's wrapper to be set
 */
void BeanProperty::setProperty(IBeanWrapper* pw)
{
	/** Property's value */
	ValueWrapper *value = new ValueWrapper(this->Type, this->StrValue, this->Managed);
	
	int rtn = pw->setBeanProperty(this->Name.c_str(), 
								this->Type.c_str(), 
								value->getValuePointer());
	// if not return 0
	if( rtn ){	
		throw new SetPropertyFailedEx("BeanProperty", "setProperty", 
			string("Set property[") + this->Name + "] of Bean[" + 
			pw->getBeanName() + "] failed!");
	}
	
	pw->addParameter((long)value);
}

/** 
 * Take out a property's value.
 * @param pw The object's wrapper to manage the value
 */
void* BeanProperty::takeoutValue(IBeanWrapper* pw)
{
	/** Property's value */
	ValueWrapper *value = new ValueWrapper(this->Type, this->StrValue, this->Managed);

	pw->addParameter((long)value);
	return value->getValuePointer();
}
