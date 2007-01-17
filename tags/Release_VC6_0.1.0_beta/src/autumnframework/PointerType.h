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

#ifndef AUTUMN_POINTERTYPE_H
#define AUTUMN_POINTERTYPE_H

#include "Basic.h"
#include "ICombinedType.h"

/** 
 * Create correctly pointer value and free it.
 * 
 * @version 0.1.0
 * @since 2006-21-02
 */

class PointerType:public ICombinedType{
public:
	/** 
	 * Create a pointer of basic type from StrValueList.
	 * @param vl A Vector<string>
	 * @param basicType Base type of the pointer value
	 * @param it A iterator pointing to the first unused string, it will be changed
	 * in this function.
	 * @return A pointer to the pointer value
	 */
	void* createValue(const StrValueList& vl, string basicType, StrIterator& it);

	/** 
	 * Free the space where p point 
	 * @param p Pointer to a pointer value
	 * @param basicType Base type of the pointer value
	*/
	void freeValue(void* p, string basicType);
	
	/** Free the space where p point, don't free it's memeber's space */
	void freeSelfSpace(void* p){
		delete (void**)p;
	}
};

#endif
