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

#include "IAutumnType.h"
#include "IBeanFactory.h"
#include "AutumnException.h"

using namespace std;

namespace Autumn{

/** 
 * Create object value and free it.
 * 
 * @version 0.1.0
 * @since 2006-21-15
 */
class ObjectType:public IAutumnType{
	
	/** Bean factory */
	IBeanFactory* Bf;

public:
	/** Constructor */
	ObjectType(IBeanFactory* p){
		this->Bf = p;
	}
	
	/** 
	 * Create a value from StrValueList(from it's first element in fact).
	 * @param vl A Vector<string>
	 * @param it A iterator pointing to the first unused string, it will be changed
	 * in this function.
	 * @return A pointer to a value of object
	 */
	virtual void* createValue(const string& type, const StrValueList& vl, 
			StrIterator& it) const{
		if( it != vl.end() ){
			string name = *it++;
			void* p = this->Bf->getBean(name, type);
			if( p != NULL ) return p;
			
			throw CreateBeanFailedEx("ObjectType", "createValue",
				"getBean[" + name + "] return NULL!");
		}
		throw NonValueEx("ObjectType", "createValue",
			"There is no string in vector!");
	}

	/** Free the space where p point */
	virtual void freeValue(void* p, const string& type){
		this->Bf->freeBean(p);
	}
	
	virtual void freeSelfSpace(void* p){
		this->Bf->freeBean(p);
	}
	
	virtual bool isThisType(const string& type) const {
		return type.compare("autumnbean") == 0;
	}
};

} // End namespace Autumn

#endif
