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

#ifndef AUTUMN_OBJECTTYPE_H
#define AUTUMN_OBJECTTYPE_H

#include "IBasicType.h"
#include "BeanFactoryImpl.h"

/** 
 * Create object value and free it.
 * 
 * @version 0.1.0
 * @since 2006-21-15
 */
class ObjectType:public IBasicType{
public:
	/** 
	 * Create a value from StrValueList(from it's first element in fact).
	 * @param vl A Vector<string>
	 * @return A pointer to a value of object
	 */
	void* createValue(StrValueList& vl){
		return (void*)BeanFactoryImpl::getInstance()->getBean(vl[0]);
	}

	/** Free the space where p point */
	void freeValue(void* p){
		BeanFactoryImpl::getInstance()->freeBean(p);
	}
	
};

#endif
