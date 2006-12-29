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

#include "PointerType.h"
#include "TypeManager.h"

/** 
 * Create correctly pointer value and free it.
 * 
 * @version 0.1.0
 * @since 2006-21-02
 */

void* PointerType::createValue(StrValueList& vl, string basicType)
{
	void* p = TypeManager::getInstance()->createValue(vl, basicType);

	void** pp = new (void*);
	*pp = p;
	return (void*)pp;
}

void PointerType::freeValue(void* p, string basicType)
{
	TypeManager::getInstance()->freeValue(*(void**)p, basicType);
	delete (void**)p;
}
