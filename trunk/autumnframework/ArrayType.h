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

#ifndef AUTUMN_ARRAYTYPE_H
#define AUTUMN_ARRAYTYPE_H

#include "ICombinedType.h"

/** 
 * Create correctly array value and free it.
 * class T: the ture type of value, it must support evaluation operator(=); 
 * createfun: the function that conversion a string to a T value;
 * freefun: the function that free the space created in createfun, for example,
 * T is a pointer to a space created in createfun;
 * 
 * @version 0.1.0
 * @since 2006-11-25
 */
template<class T, T createfun(const char*), void freefun(T)>class ArrayType:public ICombinedType{
public:
	/** 
	 * Create a value array from StrValueList.
	 * @param vl A Vector<string>
	 * @return A pointer to a value array of type T
	 */
	void* createValue(StrValueList& vl, string type=""){
		T *p = new T[vl.size()];
		T *ptmp = p;
		string cValue;
		
		// create the value array
		for(int i=0; i<vl.size(); i++){
			cValue = vl.at(i);
			*ptmp = createfun(cValue.c_str());
			ptmp++;
		}

		T** pp= new (T*);
		*pp = p;
		return (void*)pp; //*pp is the value array
	}

	/** 
	 * Free the space where p point
	 * @param pp Pointer to a value array
	 * @param arraysize the count of array elements
	 */
	void freeValue(void* pp, int arraysize, string type=""){
		T** p = (T**)pp;

		// free space for each T if necessary
		if( freefun != NULL){
			T* ptmp = *p;
			for(int i=0; i<arraysize; i++){
				freefun(*ptmp);
				ptmp++;
			}
		}

		// free space of T array
		delete *p;
		
		// free space of T*
		delete p;
	}
};

#endif
