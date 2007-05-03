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

#ifndef AUTUMN_ELMTFACTORY_H
#define AUTUMN_ELMTFACTORY_H

#include <vector>
#include "IElement.h"

using namespace std;

/** 
 * Factory to make elements of c++ head file.
 */
class ElmtFactory{
	/** this is a singleton */
	static ElmtFactory* instance;

	/** the list of elements, each type has a instance */
	vector<IElement*> Elements;

	ElmtFactory(){}

public:
	/** Get the instance of this singleton */
	ElmtFactory* getInstance();
	
	/** 
	 * make a element from string
	 * @param s Content of head file
	 * @param idx begin position to parse a element
	 */
	IElement* makeElmt(string& s, int& idx);

	~ElmtFactory();
};
#endif

