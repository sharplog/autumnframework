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

#ifndef AUTUMN_BEANPROPERTY_H
#define AUTUMN_BEANPROPERTY_H

#include <string>
#include "Basic.h"
#include "IBeanWrapper.h"

using namespace std;

/** 
 * Bean's property which will be set.
 * @version 0.1.0
 * @since 2006-11-22
 */
class BeanProperty {
private:
	
	/** Property's name */
	string Name;

	/** Property's type */
	string Type;
	
	/** String list presenting parameter value */
	StrValueList StrValue;
	
	/** Managed by Autumn framework or not */
	bool Managed;

public:
	BeanProperty(string name, string type, StrValueList& vl, bool b=true):
	  Name(name), Type(type), StrValue(vl), Managed(b){ }

	/** 
	 * Set a object's property.
	 * @param pw The object's wrapper to be set
	 */
	void setProperty(IBeanWrapper* pw);

	/** 
	 * Take out a property's value.
	 * @param pw The object's wrapper to manage the value
	 */
	void* takeoutValue(IBeanWrapper* pw);
};
#endif
