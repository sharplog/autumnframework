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

#include <memory>
#include "XMLResource.h"
#include "BeanConfig.h"
#include "BeanManager.h"
#include "IBeanFactory.h"
#include "BeanFactoryImpl.h"
#include "AutumnException.h"
#include "IBeanWrapper.h"

/** 
 * BeanFactory implementation
 *
 * @version 0.1.0
 * @since 2006-12-5
 */

/**
 * When a bean is not in dynamic library, but in main process,
 * using this factory. The second parameter of map mustn't be
 * a function type, it use void* type here and will be converse to
 * function type when using it.
 * @param string Name of bean
 * @param void* Function pointer of creating BeanWrapper
 */

IBeanFactory* BeanFactoryImpl::Instance = NULL;

/** 
 * Constructor
 * @param config Configuration resource
 */
BeanFactoryImpl::BeanFactoryImpl(IResource* config)
{
	this->Config = new AutumnConfig(config);
	this->ManagerOfBean = new BeanManager();
}

/** 
 * Get this singleton's instance
 * @param config Configuration resource
 */
IBeanFactory* BeanFactoryImpl::getInstance(IResource* config)
{
	if( BeanFactoryImpl::Instance == NULL )
		BeanFactoryImpl::Instance = new BeanFactoryImpl(config);
	return BeanFactoryImpl::Instance;
}

/** Get this singleton's instance */
IBeanFactory* BeanFactoryImpl::getInstance()
{
	if( BeanFactoryImpl::Instance != NULL )
		return BeanFactoryImpl::Instance;
	throw new NonInstanceEx("BeanFactoryImpl", "getInstance", "Instance is NULL");
}

/** 
 * Get a bean with bean's name
 * @param name Bean's name
 * @return A pointer to the bean
 */
void* BeanFactoryImpl::getBean(string name)
{
	void* p;
	int i;

	BeanConfig* bc = this->Config->getBeanConfig(name);
	// Not found
	if( bc == NULL ) return NULL;

	// If singleton
	if( bc->isSingleton() ){
		p = this->ManagerOfBean->getSingleton(name);
		if( p != NULL) return p;
	}

	// Create depended objects, they should be singletons.
	StrValueList vl = bc->getDependedObjects();
	for( i=0; i<vl.size(); i++){
		if( this->ManagerOfBean->getSingleton(vl[i]) == NULL)
			this->getBean(vl[i]);
	}

	//Use auto_ptr to free pw if exception happens?
	auto_ptr<IBeanWrapper> pw( bc->createWrapper() );

	//Create bean
	PropertyList* pargs = bc->getConArgs();
	if( pargs->size() == 0 ){	//No constructor argument
		p = pw->createBean();
	}
	else{						//Has constructor argments
		int num = pargs->size();

		typedef void* void_ptr;
		auto_ptr<void_ptr> pp( new void_ptr[num] );
		void_ptr* pv = pp.get();

		for(i=0; i<num; i++){
			pv[i] = (*pargs)[i]->takeoutValue(pw.get());
		}
		p = pw->createBean(pv, num);
	}
	if( NULL == p){
		throw new CreateBeanFailedEx("BeanFactoryImpl", "getBean", 
			string("Create Bean [") + name + "] failed!");
	}
	
	//Set properties
	PropertyList* props = bc->getProperties();
	for(i=0; i<props->size(); i++){
		(*props)[i]->setProperty(pw.get());
	}

	//Initialize bean
	if( pw->getInitializable() ){
		pw->initializeBean();
	}

	//Add to bean manager
	if( bc->isSingleton() ){
		this->ManagerOfBean->addSingleton(name, pw.release());
	}
	else{
		this->ManagerOfBean->addBean(pw.release());
	}

	return p;
}

/** 
 * Free a bean
 * @param p A pointer to the bean
 */
void BeanFactoryImpl::freeBean(void* p)
{
	this->ManagerOfBean->deleteBean(p);
}

/** 
 * A bean exists or not
 * @param name Bean's name
 * @return True if it exists, or false.
 */
bool BeanFactoryImpl::containsBean(string name)
{
	if(	this->Config->getBeanConfig(name) )
		return true;
	else
		return false;
}

/** 
 * A bean is a singleton or not
 * @param name Bean's name
 * @return True if it's a singleton, or false. If not found, also return false.
 */
bool BeanFactoryImpl::isSingleton(string name)
{
	BeanConfig* bc = this->Config->getBeanConfig(name);
	if( bc )
		return bc->isSingleton();
	else
		return false;
}

/** Get IBeanFactory instance */
IBeanFactory* getBeanFactoryWithXML(const char* file)
{
	return BeanFactoryImpl::getInstance(new XMLResource(file));
}
