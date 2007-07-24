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

namespace Autumn{

const int BeanManager::HashDivisor = 997;

BeanManager::~BeanManager()
{
	typedef void WrapperFreer (IBeanWrapper*);
	map<long, long> m;
	vector<IBeanWrapper*> vSingleton;
	IBeanWrapper* pt;
	WrapperFreer* pf;
	
	AutumnLog::getInstance()->debug("BeanManager->~BeanManager");
	
	this->Beans.listElement(m);
	for(map<long, long>::iterator it = m.begin(); it != m.end(); it++){
		long tmp;
		this->Beans.deleteElement(it->first, tmp);
		
		pt = (IBeanWrapper *)it->second;

		// Singleton will be deleted at last
		if( pt->getSingleton() ) {
			vSingleton.push_back(pt);
		}
		else{
			pf = pt->getWrapperDeleter();
			pf(pt);		//delete itself
		}
	}

	for( int i=0; i<vSingleton.size(); i++){
		pt = vSingleton[i];
		pf = pt->getWrapperDeleter();
		pf(pt);		//delete itself
	}
}
/** 
 * Delete a bean from bean manager.
 * @param p Pointer to the bean.
 */
void BeanManager::deleteBean(void* p)
{
	TPointer pw;
	typedef void WrapperFreer (IBeanWrapper*);
	
	AutumnLog::getInstance()->debug("BeanManager->deleteBean");

	// Delete from hash table
	// Maybe it has deleted somewhere, like ~BeanManager()
	if( this->Beans.deleteElement((TPointer)p, pw) ){
		IBeanWrapper* pt = (IBeanWrapper *)pw;
		
		// Singleton will be deleted at last
		if( ! pt->getSingleton() ) {
			WrapperFreer* pf = pt->getWrapperDeleter();
			pf(pt);		//delete itself
		}
	}
}

IBeanWrapper* BeanManager::releaseBean(void* p){
	TPointer pw = (TPointer)NULL;
	this->Beans.deleteElement((TPointer)p, pw);
	this->deleteSingleton(p);
	return (IBeanWrapper*)pw;
}

IBeanWrapper* BeanManager::getBeanWrapper(void* p){
	TPointer pw = (TPointer)NULL;
	this->Beans.searchElement((TPointer)p, pw);
	return (IBeanWrapper*)pw;
}

/** 
 * Add a bean
 * @param name Bean's name
 * @param pw Pointer to bean's wrapper
 */
void BeanManager::addBean(const string& name, IBeanWrapper* pw)
{
	TPointer pl = (TPointer)pw;
	this->Beans.insertElement((TPointer)pw->getBean(), pl);

	if( pw->getSingleton() )
		this->SingletonBeans.insert(make_pair(name, pw->getBean()));
}

/** 
 * Find a singleton by name
 */
void* BeanManager::getSingleton(const string& name)
{
	map<string, void*>::iterator it = this->SingletonBeans.find(name);
	if( it != this->SingletonBeans.end() )
		return it->second;

	return NULL;
}

/** 
 * Delete a singleton by pointer 
 */
void BeanManager::deleteSingleton(void* p)
{
	for(map<string, void*>::iterator it = this->SingletonBeans.begin();
			it != this->SingletonBeans.end(); it++){
		if( it->second == p){
			this->SingletonBeans.erase( it );
			break;
		}
	}
}

} // End namespace Autumn
