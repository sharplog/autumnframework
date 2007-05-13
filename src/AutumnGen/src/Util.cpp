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

#include <cctype>
#include <vector>
#include "Util.h"

using namespace std;

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
		idx = s.find("*/", 0);
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

int Util::irrelevantLen(string& s)
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

int Util::unrecognisedLen(string& s)
{
	int brace = Util::indexOf(s, '{');
	int semicolon = Util::indexOf(s, ';');

	if( string::npos == semicolon && string::npos == brace )
		return s.length();
	
	if( string::npos != semicolon && string::npos == brace )
		return semicolon + 1;

	if( string::npos != semicolon && string::npos != brace &&
			semicolon < brace )
		return semicolon + 1;

	int idx = Util::findMatching(s, '{', '}');
	if( string::npos == idx )
		return s.length();
	else
		return idx + 1;
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
		}
		else {
		   int l = skip(s.substr(i));
		   if( l > 0)
			   i += l - 1;		// -1
		}
	}
	return string::npos;
}

int Util::indexOf(string& s, string t)
{
	for( int i = 0; i < s.length(); ){
		int l;
		if( Util::startWith(s.substr(i), t) )
			return i;
		else if( l = skip(s.substr(i)) )
			i += l;
		else 
			i++;
	}
	return string::npos;
}

int Util::indexOf(string& s, char c)
{
	for (int i = 0; i < s.length(); ) {
		int l;
		if (s[i] == c)
			return i;
		else if( l = skip(s.substr(i)) )
			i += l;
		else 
			i++;
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

string Util::basenameOf(string s)
{
	string::size_type idx1 = s.find_last_of('/');
	string::size_type idx2 = s.find_last_of('\\');
	string fname;

	if( idx1 == string::npos && idx2 == string::npos )
		fname = s;
	else if( idx1 == string::npos && idx2 != string::npos )
		fname = s.substr(idx2 + 1);
	else if( idx1 != string::npos && idx2 == string::npos )
		fname = s.substr(idx1 + 1);
	else
		fname = s.substr(idx1>idx2 ? idx1 + 1 : idx2 + 1);

	string::size_type idx = fname.find_last_of('.');
	return fname.substr(0, idx);
}


string Util::dirOf(string s)
{
	string::size_type idx1 = s.find_last_of('/');
	string::size_type idx2 = s.find_last_of('\\');

	if( idx1 == string::npos && idx2 == string::npos )
		return "";
	else if( idx1 == string::npos && idx2 != string::npos )
		return s.substr(0, idx2);
	else if( idx1 != string::npos && idx2 == string::npos )
		return s.substr(0, idx1);
	else
		return s.substr(0, idx1>idx2 ? idx1 : idx2);
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

string Util::getLastWord(string s)
{
	string word;

	int idx1 = s.length() - 1;
	while( idx1 >= 0 && isspace(s[idx1]) ) idx1--;

	int idx2 = idx1;
	while( idx2 >= 0 && !isspace(s[idx2]) && !isSpecialChar(s[idx2])) idx2--;

	if( idx2 < idx1 )
		word = s.substr(idx2+1, idx1 - idx2);
	
	return word;
}

string Util::replaceComment(string s)
{
	int idx = 0, ridx;
	string rest;
	while( idx <s.size() ){
		rest = s.substr(idx);
		// can't replace /* in a literal string 
		if( ridx = Util::literalLen(rest) )
			idx += ridx;
		else if( ridx = Util::commentLen(rest) )
			s.replace(idx, ridx, 1, ' ');
		else
			idx ++;
	}

	return s;
}

string Util::trim(string s)
{
	int idx1, idx2, len = s.length();
	
	idx1 = 0, idx2 = len -1;
	while( idx1 <= len - 1 && isspace(s[idx1]) ) idx1 ++;
	while( idx2 > idx1 && isspace(s[idx2]) ) idx2 --;

	return s.substr(idx1, idx2 - idx1 + 1);
}

string Util::trimall(string s)
{
	for( int i=0; i<s.length(); )
		if( isspace(s[i]) ) 
			s.erase(i, 1);
		else
			i++;
	return s;
}

bool Util::isPrimType(string w)
{
	vector<string> primitives;
	primitives.push_back("void");
	primitives.push_back("bool");
	primitives.push_back("char");
	primitives.push_back("short");
	primitives.push_back("int");
	primitives.push_back("float");
	primitives.push_back("double");
	primitives.push_back("long");
	primitives.push_back("singed");
	primitives.push_back("unsinged");

	for( int i=0; i<primitives.size(); i++)
		if( primitives[i].compare(w) == 0 )
			return true;
		
	return false;
}

bool Util::isStruTypeKey(string w)
{
	vector<string> keys;
	keys.push_back("struct");
	keys.push_back("class");
	keys.push_back("enum");
	keys.push_back("union");

	for( int i=0; i<keys.size(); i++)
		if( keys[i].compare(w) == 0 )
			return true;

	return false;
}

string Util::toUpper(string s)
{
	string t = s;

	for( int i=0; i<t.length(); i++)
		t[i] = toupper(t[i]);

	return t;
}
