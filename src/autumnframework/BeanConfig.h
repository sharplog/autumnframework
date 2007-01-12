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

#ifndef AUTUMN_BEANCONFIG_H
#define AUTUMN_BEANCONFIG_H

#include <string>
#include <vector>
#include "IBeanWrapper.h"
#include "BeanProperty.h"
#include "ValueWrapper.h"
#include "AutumnDefinition.h"

using namespace std;

typedef vector<BeanProperty*> PropertyList;
typedef IBeanWrapper* WrapperMaker();
typedef void WrapperFreer(IBeanWrapper*);

/** 
 * Bean configuration.
 * @version 0.1.0
 * @since 2006-12-12
 */
class BeanConfig{
	
	/** Bean's name */
	string Name;

	/** The function to create bean wrapper */
	WrapperMaker *WrapperCreater;

	/** The function to free bean wrapper */
	WrapperFreer *WrapperDeleter;
	
	/** Constructor's arguments */
	PropertyList *ConArgs;
	
	/** Depended objects, should be singleton. */
	StrValueList DependedObjects;
	
	/** Bean's properties */
	PropertyList *Properties;

	/** Bean has initializing function or not */
	bool Initializable;

	/** Bean has destroying function or not */
	bool Destroyable;
	
	/** Bean is singleton or not */
	bool Singleton;

public:
	/** Constructor */
	BeanConfig(TBean& beandef, WrapperMaker* wc, WrapperFreer* wd);

	/** Constructor for customized type class */
	BeanConfig(TType& typedefine, WrapperMaker* wc, WrapperFreer* wd);
	
	/** Destructor */
	~BeanConfig();

	/** Create bean's wrapper */
	IBeanWrapper* createWrapper();
	
	/** Get constructor's arguments */
	PropertyList *getConArgs() const{
		return this->ConArgs;
	}

	/** Get bean's properties */
	PropertyList *getProperties() const{
		return this->Properties;
	}

	/** Get depended objects list */
	StrValueList& getDependedObjects() {
		return this->DependedObjects;
	}

	/** Get status of being singleton or not */
	bool isSingleton(){return this->Singleton;}
};
#endif
