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

#ifndef AUTUMN_IBEANFACTORY_H
#define AUTUMN_IBEANFACTORY_H

#include <string>

#if(defined WIN32 && defined _USRDLL)
#define DLLEXPORT _declspec(dllexport)
#define DLLIMPORT _declspec(dllimport)
#else
#define DLLEXPORT 
#define DLLIMPORT
#endif

using namespace std;

/** 
 * BeanFactory, autumn framework's interface to programmer
 *
 * @version 0.1.0
 * @since 2006-12-5
 */

class DLLEXPORT IBeanFactory{
private:
	/** The singleton's instance */
	static IBeanFactory* Instance;
	
public:
	/**
	 * Get this singleton's instance
	 * @param file Configuration xml file
	 * @return Instance of IBeanFactory
	 */
	static IBeanFactory* getInstanceWithXML(const char* file);

	/** 
	 * Get a bean with bean's name
	 * @param name Bean's name
	 * @return A pointer to the bean
	 */
	virtual void* getBean(string name) = 0;

	/** 
	 * Free a bean
	 * @param p A pointer to the bean
	 */
	virtual void freeBean(void* p) = 0;
	
	/** 
	 * A bean exists or not
	 * @param name Bean's name
	 * @return True if it exists, or false.
	 */
	virtual bool containsBean(string name) = 0;

	/** 
	 * A bean is a singleton or not
	 * @param name Bean's name
	 * @return True if it's a singleton, or false.
	 */
	virtual bool isSingleton(string name) = 0;
	
	/** 
	 * Destructor
	 */
	virtual ~IBeanFactory(){}
};
#endif
