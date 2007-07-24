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

#ifndef AUTUMN_VALUEWRAPPER_H
#define AUTUMN_VALUEWRAPPER_H

#include <string>
#include "Basic.h"
#include "TypeManager.h"
#include "IAutumnType.h"

using namespace std;

namespace Autumn{

/**
 * Parameter value for class constuctor or setter functions.
 * 
 * @since 2006-11-22
 * @version 0.1.0
 */
class ValueWrapper{
private:
	/** Type of the argument */
	string Type;

	/** Managed by Autumn framework or not */
	bool Managed;
	
	/** Pointer to the argument */
	void*  PointerOfValue;

	/** Type Bean to create or delete value */
	IAutumnType* TypeBean;

public:
	
	/** 
	 * Constructor a new ValueWrapper with type and value
	 * @param type Type of the argument
	 * @param vl Value string list of the argument
	 * @param managed This value is managed by Autumn or not
	 * @param at TypeBean to create and delete value
	 */
	ValueWrapper(const string& type, StrValueList& vl, bool managed,
				 IAutumnType* at);
	
	/** Destructor, delete pointer of value */
	~ValueWrapper();

	/** 
	 * Return the address of pointer to the argument's value. 
	 */
	void*  getValuePointer(){
		return this->PointerOfValue;
	}
};

} // End namespace Autumn
#endif
