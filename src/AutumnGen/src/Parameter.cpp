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

#include "Util.h"
#include "Parameter.h"

Parameter::Parameter(string s){
	this->IsConst = false;
	this->IsReference = false;
	
	string pstr = Util::trim(s);
	if( pstr.empty() )
		return;

	int idx = pstr.find('=', 0);
	if( string::npos != idx ){
		this->DefaultValue = Util::trim(pstr.substr(idx + 1));
		pstr = Util::trim(pstr.substr(0, idx));
	}
	
	string conStr("const");
	if( Util::startWith(pstr, conStr) ){
		this->IsConst = true;
		pstr = Util::trim( pstr.substr(conStr.length()) );
	}

	// parsing name should be after parsing "const", 
	// can cope with parameter like "const classXXX"
	bool hasName = true;
	int arrIdx = pstr.find_first_of('[');
	int nameIdx;
	string nameStr = Util::getLastWord(pstr.substr(0, arrIdx));
	
	if( nameStr.empty() )
		hasName = false;
	else {
		nameIdx = Util::indexOf(pstr, nameStr);
		if( 0 == nameIdx )		// only one word, must be a type
			hasName = false;
		else if( Util::isPrimType(nameStr) )
			hasName = false;
		else if( Util::isStruTypeKey(Util::trim(pstr.substr(0, nameIdx))) )
			hasName = false;
	}
	
	if( hasName ){
		this->Name = nameStr;
		pstr = Util::trim( pstr.erase(nameIdx, nameStr.length()) );
	}

	if( pstr[pstr.length() - 1] == '&' ){
		this->IsReference = true;
		pstr = Util::trim( pstr.substr(0, pstr.length() - 1) );
	}

	this->Type = pstr;
}
