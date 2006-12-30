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

#ifndef AUTUMN_BASICTYPE_H
#define AUTUMN_BASICTYPE_H

#include "IBasicType.h"

/** 
 * Create correctly value and free it.
 * class T: the ture type of value, it must support evaluation operator(=); 
 * createfun: the function that conversion a string to a T value;
 * freefun: the function that free the space created in createfun, for example,
 * T is a pointer to a space created in createfun;
 * 
 * @version 0.1.0
 * @since 2006-11-25
 */
template<class T, T createfun(const char*), void freefun(T)>class BasicType:public IBasicType{
public:
	/** 
	 * Create a value from StrValueList(from it's first element in fact).
	 * @param vl A Vector<string>
	 * @return A pointer to a value of type T
	 */
	void* createValue(StrValueList& vl);

	/** Free the space where p point */
	void freeValue(void* pp);
};

template<class T, T createfun(const char*), void freefun(T)>
void* BasicType<T, createfun, freefun>::createValue(StrValueList& vl)
{
	T *p = new T;
	string cValue = vl[0];
	*p = createfun(cValue.c_str());
	return (void*)p; //*p is the value
}

template<class T, T createfun(const char*), void freefun(T)>
void BasicType<T, createfun, freefun>::freeValue(void* pp){
	T* p = (T*)pp;
	// free space for T if necessary
	if( freefun != NULL){
		freefun(*p);
	}
	
	// free space of T
	delete p;
}

#endif
