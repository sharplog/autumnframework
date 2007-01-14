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
#include "ObjectType.h"

/** 
 * BeanFactory implementation
 *
 * @version 0.1.0
 * @since 2006-12-5
 */
const char* LogBeanName = "AutumnFrameworkLog";

IBeanFactory* BeanFactoryImpl::Instance = NULL;

/** 
 * Constructor
 * @param config Configuration resource
 */
BeanFactoryImpl::BeanFactoryImpl(IResource* config)
{
	this->Config = new AutumnConfig(config);
	this->ManagerOfBean = new BeanManager();
	this->ManagerOfType = new TypeManager();

	// Add each bean as a basic type. Do this before adding customized types,
	// or the customized types will be added to type manager twice.
	vector<string> beanClasses = this->Config->getAllBeanClasses();
	for(int i = 0; i<beanClasses.size(); i++)
		this->ManagerOfType->setBasicType(beanClasses[i], new ObjectType);

	// Add customized types
	vector<TypeConfig>* types = this->Config->getAllTypes();
	for(int j = 0; j<types->size(); j++){
		TypeConfig tc = (*types)[j];
		this->Config->setBeanConfig(tc.Name, tc.BeanCfg);

		void* p = this->getBean(tc.Name);
		if( tc.IsBasic ) {
			this->ManagerOfType->setBasicType(tc.Name, (IBasicType*)p, true);
		}
		else{
			ICombinedType* pc = (ICombinedType*)p;
			pc->setTypeManager(this->ManagerOfType);
			this->ManagerOfType->setCombinedType(tc.Name, pc, true);
		}
	}
	
	// use logger configured by user
	void* p = this->getBean(LogBeanName);
	if( p != NULL ){
		AutumnLog::getInstance()->injectLogger((ILogAdapter*)p);
	}
}

/** Destructor */
BeanFactoryImpl::~BeanFactoryImpl()
{
	AutumnLog::getInstance()->setDefaultLogger();
	
	AutumnLog::getInstance()->debug("BeanFactoryImpl->~BeanFactoryImpl");

	delete this->Config;
	delete this->ManagerOfBean;
	BeanFactoryImpl::Instance = NULL;
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
			pv[i] = (*pargs)[i]->takeoutValue(pw.get(), this->ManagerOfType);
		}
		p = pw->createBean(pv, num);
	}
	if( NULL == p){
		throw new CreateBeanFailedEx("BeanFactoryImpl", "getBean", 
			string("Create Bean [") + name + "] failed!");
	}
	
	//Set singleton
	pw->setSingleton(bc->isSingleton());

	//Set properties
	PropertyList* props = bc->getProperties();
	for(i=0; i<props->size(); i++){
		(*props)[i]->setProperty(pw.get(), this->ManagerOfType);
	}

	//Initialize bean
	if( pw->getInitializable() ){
		pw->initializeBean();
	}

	//Add to bean manager
	this->ManagerOfBean->addBean(name, pw.release());

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

/** Delete IBeanFactory instance */
void deleteBeanFactory(IBeanFactory* p)
{
	delete p;
}
