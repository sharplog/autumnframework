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

#include "ValueWrapper.h"
#include "BeanManager.h"
#include "AutumnLog.h"

/** 
 * Maintains all created beans and dependence ralations in them.
 * @version 0.1.0
 * @since 2006-12-18
 */

const int BeanManager::HashDivisor = 997;

BeanManager::~BeanManager()
{
	typedef void WrapperFreer (IBeanWrapper*);
	map<long, long> m;

	AutumnLog::getInstance()->debug("BeanManager->~BeanManager");
	
	this->Beans.listElement(m);
	for(map<long, long>::iterator it = m.begin();
			it != m.end(); it++){
		long tmp;
		this->Beans.deleteElement(it->first, tmp);
		
		IBeanWrapper* pt = (IBeanWrapper *)it->second;
		WrapperFreer* pf = pt->getWrapperDeleter();
		//delete itself
		pf(pt);
	}

}
/** 
 * Delete a bean from bean manager.
 * @param p Pointer to the bean.
 */
void BeanManager::deleteBean(void* p)
{
	long pw;
	typedef void WrapperFreer (IBeanWrapper*);
	
	AutumnLog::getInstance()->debug("BeanManager->deleteBean");

	// Delete from hash table
	// Maybe it has deleted somewhere, like ~BeanManager()
	if( this->Beans.deleteElement((long)p, pw) ){
		IBeanWrapper* pt = (IBeanWrapper *)pw;
		WrapperFreer* pf = pt->getWrapperDeleter();
		//delete itself
		pf(pt);
	}
}

/** 
 * Add a bean
 * @param pw Pointer to bean's wrapper
 */
void BeanManager::addBean(IBeanWrapper* pw)
{
	long pl = (long)pw;
	this->Beans.insertElement((long)pw->getBean(), pl);
}

/** 
 * Add a singleton bean
 * @param name Singleton's name
 * @param pw Pointer to singleton's wrapper
 */
void BeanManager::addSingleton(string name,IBeanWrapper* pw)
{
	long pl = (long)pw;
	this->Beans.insertElement((long)pw->getBean(), pl);

	this->SingletonBeans.insert(make_pair(name, pw->getBean()));
}

/** 
 * Find a singleton by name
 */
void* BeanManager::getSingleton(string name)
{
	map<string, void*>::iterator it = this->SingletonBeans.find(name);
	if( it != this->SingletonBeans.end() )
		return it->second;

	return NULL;
}
