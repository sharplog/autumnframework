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

int Util::lineno(string& s, int idx)
{
    int n = 0;
    for(int i = 0; i < idx && i < s.length(); i++)
        if ('\n' == s[i])
            n++;
    return n;
}

int Util::whiteSapceLen(string& s)
{
	int n = 0;
	while( n < s.size() && isspace(s[n]) ) n++;
	return n;
}

int Util::commentLen(string& s)
{
	int idx, delta;

	if( s.empty() || s.length() < 2 )
		return 0;

	if( s.compare(0, 2, "//") == 0 ){
		idx = s.find_first_of('\n');
		delta = 1;
	}
	else if( s.compare(0, 2, "/*") == 0 ){
		idx = s.find_first_of("*/");
		delta = 2;
	}
	else{
		return 0;
	}

	if( idx == string::npos )
		return s.length();		// the whole s
	else
		return idx + delta;
}

int Util::preProcessortLen(string& s)
{
	if( s.empty() || s[0] != '#' )
		return 0;

	int idx = s.find_first_of('\n');
	while( string::npos != idx && '\\' == s[idx-1] ) {
		idx = s.find_first_of('\n', idx + 1);
	}

	if( string::npos != idx )
		return idx + 1;
	else
		return s.length();		// the whole s
}

int Util::literalLen(string& s)
{
	if( s.empty() || (s[0] != '"' && s[0] != '\'') )
		return 0;

	bool escape = false;
	char c0 = s[0];
	for( int i = 1; i < s.length(); i++ ) {
	   if( !escape && s[i] == c0 )
		   return i+1;

	   if( '\\' == s[i] )
		   escape = !escape;
	   else
		   escape = false;
	}
	return 0;
}

int Util::irrelevantLen(string&s)
{
	int w, c, p, l;
	string rest = s;

	l = 0;
	do {
		if( w = Util::whiteSapceLen(rest) )
			rest = rest.substr(w);
		if( c = Util::commentLen(rest) )
			rest = rest.substr(c);
		if( p = Util::preProcessortLen(rest))
			rest = rest.substr(p);
		l = l + w + c + p;
	} while( w + c + p > 0 );
	return l;
}

int Util::findMatching(string& s, char c1, char c2)
{
	int depth = 0;
	for( int i = 0; i < s.length(); i++ ) {
	   if( s[i] == c1 )
		   depth++;
	   else if( s[i] == c2 ) {
		   depth--;
		   if( depth == 0 )
			   return i;
	   } else {
		   i += skip(s.substr(i));
	   }
	}
	return string::npos;
}

int Util::indexOf(string& s, string t)
{
	for( int i = 0; i < s.length(); i++ ){
		if( Util::startWith(s.substr(i), t) )
			return i;
		else
			i += skip(s.substr(i));
	}
	return string::npos;
}

int Util::indexOf(string& s, char c)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == c)
			return i;
		else
			i += skip(s.substr(i));
	}
	return string::npos;
}
	
bool Util::startWith(string& s, string t)
{
	if( s.empty() || t.empty() ) return false;
	if( s.compare(0, t.length(), t) != 0 ) return false;
	if( s.length() == t.length() ) return true;
	if( isspace(s[t.length()])) return true;
	if( Util::isSpecialChar(s[t.length()])) return true;
	return false;
}

string Util::filenameOf(string s)
{
	int idx1 = s.find_last_of(s, "/");
	int idx2 = s.find_last_of(s, "\\");

	if( idx1 == string::npos && idx2 == string::npos ) return s;
	if( idx1 == string::npos && idx2 != string::npos ) return s.substr(idx2);
	if( idx1 != string::npos && idx2 == string::npos ) return s.substr(idx1);
	return s.substr(idx1>idx2 ? idx1 : idx2);
}

bool Util::isSpecialChar(char c)
{
	if( c == '_' ) return false;
	if( isalnum(c) ) return false;
	return true;
}

int Util::skip(string& s)
{
	int w, c, t, l;
	string rest = s;

	l = 0;
	do {
		if( w = Util::whiteSapceLen(rest) )
			rest = rest.substr(w);
		if( c = Util::commentLen(rest) )
			rest = rest.substr(c);
		if( t = Util::literalLen(rest))
			rest = rest.substr(t);
		l = l + w + c + t;
	} while( w + c + t > 0 );
	return l;
}