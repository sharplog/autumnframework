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

#ifndef AUTUMN_BEANMANAGER_H
#define AUTUMN_BEANMANAGER_H

#include <string>
#include <vector>
#include "Basic.h"
#include "IBeanWrapper.h"
#include "MapHashTable.h"

using namespace std;

/** 
 * Maintains all created beans and dependence ralations in them.
 * @version 0.1.0
 * @since 2006-12-9
 */

class BeanManager{
private:
	/** Divisor for hash table */
	static const int HashDivisor;

	/** All beans */
//	MapHashTable<IBeanWrapper*, unsigned long> Beans;
	MapHashTable<long, long> Beans;
	
	/** Singleton beans */
	map<string, void*> SingletonBeans;
	
public:
	/** Constructor */
	BeanManager():Beans(BeanManager::HashDivisor){}

	/** Destructor */
	~BeanManager();
	
	/** 
	 * Delete a bean from bean manager.
	 * @param p Pointer to the bean.
	 */
	void deleteBean(void* p);

	/** 
	 * Add a bean
	 * @param pw Pointer to bean's wrapper
	*/
	void addBean(IBeanWrapper* pw);
		
	/** 
	 * Add a singleton bean
	 * @param name Singleton's name
	 * @param pw Pointer to singleton's wrapper
	*/
	void addSingleton(string name, IBeanWrapper* pw);

	/** 
	 * Find a singleton by name
	 */
	void* getSingleton(string name);
};
#endif
