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

#include <map>
#include "Configuration.h"

using namespace std;

string Configuration::ClassWrapperSuffix = "_Wrapper";
string Configuration::FileWrapperSuffix = "_Wrapper";
string Configuration::HeadFileSuffix = ".h";
string Configuration::ImplFileSuffix = ".cpp";
string Configuration::OutPath = "";

void Configuration::setConfigs(map<string, string>& cons)
{
	map<string, string>::iterator it = cons.begin();
	while( it != cons.end() ){
		if( it->first.compare("-out") == 0 )
			Configuration::OutPath = it->second;
		else if( it->first.compare("-hsuf") == 0 )
			Configuration::HeadFileSuffix = it->second;
		else if( it->first.compare("-isuf") == 0 )
			Configuration::ImplFileSuffix = it->second;
		else if( it->first.compare("-wsuf") == 0 )
			Configuration::FileWrapperSuffix = it->second;

		it++;
	}
}

