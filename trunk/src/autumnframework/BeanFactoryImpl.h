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

#ifndef AUTUMN_BEANFACTORYIMPL_H
#define AUTUMN_BEANFACTORYIMPL_H

#include "IBeanFactory.h"
#include "IResource.h"
#include "AutumnConfig.h"
#include "BeanManager.h"
#include "TypeManager.h"

namespace Autumn{

/** 
 * BeanFactory implementation
 *
 * @version 0.1.0
 * @since 2006-12-5
 */

class BeanFactoryImpl:public IBeanFactory{
private:
	/** 
	 * Autumn configuration
	 */
	AutumnConfig* Config;

	/** 
	 * Autumn bean manager
	 */
	BeanManager* ManagerOfBean;

	/** 
	 * Autumn type manager
	 */
	TypeManager* ManagerOfType;

public:
	/** 
	 * Constructor
	 * @param config Configuration resource
	 */
	BeanFactoryImpl(IResource* config);

	/** 
	 * Get a bean with bean's name
	 * @param name Bean's name
	 * @param basename Bean's base class name
	 * @return A pointer to the bean or to its base class
	 */
	virtual void* getBean(const string name, const string basename = "");

	/** 
	 * Free a bean
	 * @param p A pointer to the bean
	 */
	virtual void freeBean(void* p);
	
	/** 
	 * A bean exists or not
	 * @param name Bean's name
	 * @return True if it exists, or false.
	 */
	virtual bool containsBean(string name);

	/** 
	 * A bean is a singleton or not
	 * @param name Bean's name
	 * @return True if it's a singleton, or false.
	 */
	virtual bool isSingleton(string name);

	/** Destructor */
	virtual ~BeanFactoryImpl();
};

} // End namespace Autumn
#endif
