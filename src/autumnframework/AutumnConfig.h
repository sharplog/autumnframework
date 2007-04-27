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

#ifndef AUTUMN_AUTUMNCONFIG_H
#define AUTUMN_AUTUMNCONFIG_H

#include <string>
#include <map>
#include <vector>
#include "IResource.h"
#include "ILibrary.h"
#include "BeanConfig.h"

using namespace std;

/** 
 * Autumn configuration, include bean, library.
 * @version 0.1.0
 * @since 2006-12-6
 */
class AutumnConfig{
	/** All dynamic libraries */
	vector<ILibrary*> Libs;

	/** All Beans */
	map<string, BeanConfig*> Beans;

	/** All customized types,  */
	vector<string> TypeNames;
	
	/** Deal with each dynamic library */
	void processLibrary(TLibrary& lib);

	/** Deal with each bean */
	void processBean(TBean& bean, ILibrary* pl);
	
	/** 
	 * Name mangler
	 * @param objType Type of object
	 * @param op Operation on object
	 * @param objName Name of object
	 */
	string mangleName(string objType, string  op, string objName);

public:
	/** Constructor */
	AutumnConfig(IResource* config);

	/** Destructor */
	~AutumnConfig();
	
	/** Set a bean's configuration */
	void setBeanConfig(string name, BeanConfig* pb){
		this->Beans.insert(make_pair(name, pb));
	}

	/** Get a bean's configuration by name */
	BeanConfig* getBeanConfig(string name);
	
	/** Get all customized types */
	vector<string>* getAllTypes(){
		return &this->TypeNames;
	}
};
#endif
