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

#ifndef AUTUMN_LOCALLIBRARY_H
#define AUTUMN_LOCALLIBRARY_H

#include <string>
#include <map>
#include "ILibrary.h"

using namespace std;

/** 
 * Local library, in main process
 * @version 0.1.0
 * @since 2006-12-16
 */

const string LocalLibraryPath = "local";

class LocalLibrary: public ILibrary{
private:
	map<string, void*> LocalFunctions;
		
	static LocalLibrary* instance;
public:
	static LocalLibrary* getInstance();

	void addFunction(const char* name, void* fun){
		this->LocalFunctions.insert(make_pair(name, fun));
	}

	void* getFunction(string name);
};

#endif
