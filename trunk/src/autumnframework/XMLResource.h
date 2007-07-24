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

#ifndef AUTUMN_XMLRESOURCE_H
#define AUTUMN_XMLRESOURCE_H

#include <vector>
#include <string>
#include "xmlParser.h"
#include "IResource.h"
#include "AutumnDefinition.h"

namespace Autumn{

/** 
 * Parse XML configuration file
 * @version 0.1.0
 * @since 2006-12-18
 */
class XMLResource: public IResource{
private:
	/** All libraries configuration */
	vector<TLibrary*> LibsConfig;

	/** Parse library */
	void parseLibrary(XMLNode& xml, TLibrary& lib);

	/** Parse bean */
	void parseBean(XMLNode& xml, TBean& bean);

	/** Parse Property */
	void parseProperty(XMLNode& xml, TProperty& prop, bool isProp);

	/** Get parsing error message */
	string getErrorMsg(XMLResults& err, const char* tag);

	/** convert value to true or false */
	bool boolAttribute(const string& value, const string& name);
public:
	/** 
	 * Constructor, parse XML file 
	 * @param path XML file path
	 */
	XMLResource(const char* path);

	/** Destructor */
	~XMLResource(){
		for(int i=0; i<this->LibsConfig.size(); i++)
			delete this->LibsConfig[i];
	}

	/** Return all libraries configuration */
	const vector<TLibrary*>* getLibraries() const{
		return &this->LibsConfig;
	}
};

} // End namespace Autumn
#endif
