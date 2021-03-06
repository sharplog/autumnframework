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
#include "Basic.h"
#include "ValueWrapper.h"
#include "IAutumnType.h"
#include "BeanProperty.h"
#include "AutumnException.h"

namespace Autumn{

void BeanProperty::setProperty(IBeanWrapper* pw, TypeManager* tm)
{
	IAutumnType* at = tm->findTypeBean(this->Type);
	
	/** Property's value */
	auto_ptr<ValueWrapper>value(new ValueWrapper(this->Type, 
				this->StrValue, this->Managed, at));
	
	int rtn = pw->setBeanPropertyValue(this->Name.c_str(), 
								value->getValuePointer());
	
	// if not return 0
	if( rtn ){	
		throw SetPropertyFailedEx("BeanProperty", "setProperty", 
			string("Set property[") + this->Name + "] of Bean[" + 
			pw->getBeanName() + "] failed!");
	}
	
	pw->addParameter((TPointer)value.release());
}

void* BeanProperty::takeoutValue(IBeanWrapper* pw, TypeManager* tm)
{
	IAutumnType* at = tm->findTypeBean(this->Type);
	
	/** Property's value */
	auto_ptr<ValueWrapper> value( new ValueWrapper(this->Type, 
				this->StrValue, this->Managed, at));

	pw->addParameter((TPointer)value.get());
	return value.release()->getValuePointer();
}

} // End namespace Autumn
