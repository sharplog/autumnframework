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

#include "Basic.h"
#include "IAutumnType.h"
#include "AutumnException.h"

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
template<class T, T createfun(const char*), void freefun(T)>class BasicType:public IAutumnType{
public:
	/** 
	 * Create a value from StrValueList(from it's first element in fact).
	 * @param vl A Vector<string>
	 * @param it A iterator pointing to the first unused string, it will be changed
	 * in this function.
	 * @return A pointer to a value of type T
	 */
	virtual void* createValue(const string type, const StrValueList& vl, StrIterator& it);

	/** Free the space where p points */
	virtual void freeValue(void* pp, const string type){
		this->freeSelfSpace(pp);
	}
	
	/** Free the space where p points, don't free it's memeber's space */
	virtual void freeSelfSpace(void* p);
};

template<class T, T createfun(const char*), void freefun(T)>
void* BasicType<T, createfun, freefun>::createValue(const string type, const StrValueList& vl, StrIterator& it)
{
	if( it != vl.end() ){
		T *p = new T;
		*p = createfun((*it++).c_str());
		return (void*)p; //*p is the value
	}
	throw new NonValueEx("BasicType", "createValue",
		"There is no string in vector!");
}

template<class T, T createfun(const char*), void freefun(T)>
void BasicType<T, createfun, freefun>::freeSelfSpace(void* pp){
	T* p = (T*)pp;
	// free space for T if necessary
	if( freefun != NULL){
		freefun(*p);
	}
	
	// free space of T
	delete p;
}

#endif
