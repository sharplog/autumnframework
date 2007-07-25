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

#include "DocCommentElmt.h"

vector<string> DocCommentElmt::valueOfTag(const string& tag)
{
	vector<string> values;
	string& s = this->Comment;
	string t = "@" + tag;
	int idx = 0;

	while( string::npos != (idx = s.find(t, idx)) ){
		int idx1 = idx + t.length();
		// @tag is embedded in a longer word
		if( (idx > 0 && !isspace(s[idx-1])) || !isspace(s[idx1]) )
			continue;
		
		while( idx < s.length() && isspace(s[idx1]) ) idx1++;
		int idx2 = idx1;
		while( idx < s.length() && !isspace(s[idx2]) ) idx2++;
		values.push_back(s.substr(idx1, idx2 - idx1));

		idx = idx2;
	}

	return values;
}

