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

#ifndef AUTUMN_PROPERTYDEFINITION_H
#define AUTUMN_PROPERTYDEFINITION_H

#include <string>
#include "Basic.h"

using namespace std;

namespace Autumn{

/** 
 * Contains property's information
 * @version 0.1.0
 * @since 2006-11-23
 */
class PropertyDefinition{
private:
	/** Property's name */
	string Name;

	/** Property value's type */
	string Type;

	/** 
	 * Property's value string. If Type is Object, Value will be a object's
	 * name. 
	 */
	StrValueList Value;

public:
	/** Create a new PropertyDefine */
	PropertyDefinition(const string& name, const string& type,
						StrValueList value){
		this->Name = name;
		this->Type = type;
		this->Value = value;
	}

	/** Return property's name */
	string getName() const {
		return this->Name;
	}

	/** Return property value's type */
	string getType() const {
		return this->Type;
	}

	/** Return the string list of property's value */
	const StrValueList& getValueString() const {
		return this->Value;
	}
};

} // End namespace Autumn
#endif
