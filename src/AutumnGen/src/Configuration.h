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

#ifndef AUTUMNGEN_CONFIGURATION_H
#define AUTUMNGEN_CONFIGURATION_H

#include <string>

using namespace std;

class Configuration{
	/** suffix of wrapper class name, like _Wrapper */
	static string ClassWrapperSuffix;

	/** suffix of wrapper file name, like _Wrapper */
	static string FileWrapperSuffix;

	/** suffix of head file, like .h, .hh, etc */
	static string HeadFileSuffix;

	/** suffix of implementation file, like .cpp, .cc, etc */
	static string ImplFileSuffix;

public:
	static string getCWS()	{
		return Configuration::ClassWrapperSuffix;
	}

	static string getFWS(){
		return Configuration::FileWrapperSuffix;
	}

	static string getHFS(){
		return Configuration::HeadFileSuffix;
	}
	
	static string getIFS(){
		return Configuration::ImplFileSuffix;
	}
};

#endif
