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

#ifndef AUTUMN_TYPEMANAGER_H
#define AUTUMN_TYPEMANAGER_H

#include <string>
#include <vector>
#include "IAutumnType.h"

/** 
 * Maitain all TypeBeans.
 * 
 * @version 0.1.0
 * @since 2006-11-25
 */

class TypeManager{
private:
	
	/** 
	 * TypeBeans 
	 * @param string Basic ValueType's name
	 */
	vector<IAutumnType*> TypeList;

	/** Customized types 
	vector<IAutumnType*> CustomizedTypes;
*/
	IAutumnType* beanMaker;
	
	/** a type is customized or not 
	bool isCustomized(IAutumnType* p);

	void addCustomizedType(IAutumnType* p);
	*/
public:
	/** 
	 * Constructor, initialize the inliine type
	 */
	TypeManager();

	/** 
	 * Destructor
	 */
	~TypeManager();
	
	/** 
	 * Set a couple of name and AutumnType into list
	 * @param name Type name
	 * @param bt A pointer to BasicType
	*/
	void addTypeBean(IAutumnType* at);
	
	/** 
	 * Erase a couple of name and ValueType from list
	 * @param name Type name
	 */
	IAutumnType* findTypeBean(string name);

	void setBeanMaker(IAutumnType* p){
		this->beanMaker = p;
	}

};

#endif
