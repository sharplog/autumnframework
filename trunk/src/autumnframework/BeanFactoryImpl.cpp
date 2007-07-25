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
#include "IAutumnType.h"
#include "ObjectType.h"

/** 
 * BeanFactory implementation
 *
 * @version 0.1.0
 * @since 2006-12-5
 */
namespace Autumn{

const char* LogBeanName = "AutumnFrameworkLog";

/** 
 * Constructor
 * @param config Configuration resource
 */
BeanFactoryImpl::BeanFactoryImpl(IResource* config)
{
	this->Config = new AutumnConfig(config);
	this->ManagerOfBean = new BeanManager();
	this->ManagerOfType = new TypeManager();

	// Add a bean maker to TypeManager to make all beans.
	// it is deleted in TypeManager destructor.
	IAutumnType* pt = new ObjectType(this);
	pt->setTypeManager(this->ManagerOfType);
	this->ManagerOfType->setBeanMaker(pt);
	
	// Add customized types
	// it is deleted in TypeManager destructor.
	vector<string>* types = this->Config->getAllTypes();
	for(int j = 0; j<types->size(); j++){
		IAutumnType* pt =(IAutumnType*) this->getBean((*types)[j]);
		pt->setTypeManager(this->ManagerOfType);
		IBeanWrapper* pw = this->ManagerOfBean->releaseBean(pt);
		this->ManagerOfType->addTypeBean(pw);
	}
	
	// use logger configured by user
	void* p = this->getBean(LogBeanName, "ILogAdapter");
	if( p != NULL ){
		AutumnLog::getInstance()->injectLogger((ILogAdapter*)p);
	}
}

/** Destructor */
BeanFactoryImpl::~BeanFactoryImpl()
{
	AutumnLog::getInstance()->setDefaultLogger();
	
	AutumnLog::getInstance()->debug("BeanFactoryImpl->~BeanFactoryImpl");

	delete this->ManagerOfBean;
	delete this->ManagerOfType;

	// Config will be used when deleting ManagerOfBean.
	delete this->Config;
}

/** 
 * Get a bean with bean's name
 * @param basename Bean's base class name
 * @return A pointer to the bean or to its base class
 */
void* BeanFactoryImpl::getBean(const string& name, const string& basename)
{
	void* p;
	int i;

	BeanConfig* bc = this->Config->getBeanConfig(name);
	// Not found
	if( bc == NULL ){
		AutumnLog::getInstance()->error("BeanFactoryImpl->getBean: bean[" +
				name + "]'s config is not found");
		return NULL;
	}

	// If singleton
	if( bc->isSingleton() ){
		p = this->ManagerOfBean->getSingleton(name);
		if( p != NULL) 
			return this->ManagerOfBean->getBeanWrapper(p)->cast2Base(basename);
	}

	// Create depended objects, they should be singletons.
	const StrValueList vl = bc->getDependedObjects();
	for( i=0; i<vl.size(); i++){
		if( this->ManagerOfBean->getSingleton(vl[i]) == NULL)
			this->getBean(vl[i]);
	}

	//Use auto_ptr to free pw if exception happens?
	auto_ptr<IBeanWrapper> pw(bc->createWrapper());

	// if use factory, use factory's wrapper to create bean.
	// pwc only to create bean, it may be bean wrapper or factory's wrapper.
	IBeanWrapper* pwc = NULL;
	if( ! bc->getFactoryBeanName().empty()) {
		void* pf = this->getBean(bc->getFactoryBeanName());
		if( pf == NULL){
			throw CreateBeanFailedEx("BeanFactoryImpl", "getBean", 
				string("Create Bean [") + name + "] failed! Get factory [" +
				bc->getFactoryBeanName() + "] failed!");
		}
		pwc = this->ManagerOfBean->getBeanWrapper(pf);
	}
	if( NULL == pwc ) pwc = pw.get();

	//Create bean
	typedef void* void_ptr;
	string conMethod = bc->getConMethod();
	PropertyList* pargs = bc->getConArgs(pwc);
	int num = pargs->size();
	if( num > 0 ){	//Has constructor arguments
		auto_ptr<void_ptr> pp( new void_ptr[num] );
		void_ptr* pv = pp.get();

		for(i=0; i<num; i++){
			// add argument into pw, not pwc
			pv[i] = (*pargs)[i]->takeoutValue(pw.get(), this->ManagerOfType);
		}
		p = pwc->execCreateMethod(conMethod, pv, num);
	}
	else{
		void_ptr* pDummy = NULL;
		p = pwc->execCreateMethod(conMethod, pDummy, num);
	}	

	if( NULL == p){
		throw CreateBeanFailedEx("BeanFactoryImpl", "getBean", 
			string("Create Bean [") + name + "] failed!");
	}
	//if bean created by factory, it should be set into pw.
	if( ! bc->getFactoryBeanName().empty()) {
		pw->setBean(p);
	}

	//Set properties
	PropertyList* props = bc->getProperties();
	for(i=0; i<props->size(); i++){
		(*props)[i]->setProperty(pw.get(), this->ManagerOfType);
	}

	//Initialize bean
	string initmethod = pw->getInitMethod();
	if( !initmethod.empty() ){
		pw->execVoidMethod(initmethod, NULL, 0);
	}

	IBeanWrapper* pw_tmp = pw.get();
	//Add to bean manager
	this->ManagerOfBean->addBean(name, pw.release());

	return pw_tmp->cast2Base(basename);
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
bool BeanFactoryImpl::containsBean(const string& name) const
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
bool BeanFactoryImpl::isSingleton(const string& name) const
{
	BeanConfig* bc = this->Config->getBeanConfig(name);
	if( bc )
		return bc->isSingleton();
	else
		return false;
}

/** Get IBeanFactory */
IBeanFactory* getBeanFactoryWithXML(const char* xmlFile)
{
	return new BeanFactoryImpl(new XMLResource(xmlFile));
}

/** Delete IBeanFactory */
void deleteBeanFactory(IBeanFactory* p)
{
	delete p;
}

} // End namespace Autumn
