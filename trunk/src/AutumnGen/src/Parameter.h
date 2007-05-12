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

#ifndef AUTUMN_PARAMETER_H
#define AUTUMN_PARAMETER_H

#include <string>

class Parameter{
	/** Type is pure data type, doesn't contain "const" or '&' */
	string Type;

	bool IsConst;
	bool IsReference;
	
	string Name;
	string DefaultValue;

public:
	Parameter(string s);

	string getType(){
		return this->Type;
	}

	bool isConst(){
		return this->IsConst;
	}

	bool isReference(){
		return this->IsReference;
	}

	bool isVoid(){
		return 0 == this->Type.compare("void");
	}
};

#endif
