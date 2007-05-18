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

#include <sstream>
#include "GenException.h"
#include "Util.h"
#include "ElmtFactory.h"
#include "MethodElmt.h"

MethodElmt::MethodElmt()
{
	this->KnownAttrs.push_back("virtual");
	this->KnownAttrs.push_back("static");
	this->KnownAttrs.push_back("inline");

	this->IsStatic = false;
	this->IsVirtual = false;
	this->PureVirtual = false;
}

bool MethodElmt::isThisType(string& s, int idx)
{
	string rest = s.substr(idx);

	if ( Util::startWith(rest, "typedef") )
		return false;
	if ( Util::startWith(rest, "friend") )
		return false;

	int semicolon = Util::indexOf(rest, ';');
	int brace = Util::indexOf(rest, '{');
	int bracket = Util::indexOf(rest, '(');

	if( string::npos == bracket )
		return false;
	if( semicolon != string::npos && semicolon < bracket )
		return false;
	if( brace != string::npos &&  brace < bracket ) 
		return false;
	
	return true;
}

//
// Only process method like: void f(){}
// Can't process method like: void(* ff(void(*fp)()))(){ return fp; } and
// void(*(*fg(int*()))(void(*)()))(){ return &ff; }
//
IElement* MethodElmt::clone(string& s, int& idx0)
{
	string rest = s.substr(idx0);
	int endbracket = Util::findMatching(rest, '(', ')');
	string mthdstr = Util::replaceComment(rest.substr(0, endbracket + 1));

	MethodElmt* e = new MethodElmt;

	int bracket = Util::indexOf(mthdstr, '(');
	string hs = mthdstr.substr(0, bracket);

	e->IsVirtual = ( string::npos != Util::indexOf(hs, "virtual") );
	e->IsStatic = ( string::npos != Util::indexOf(hs, "static") );

	this->parseNameAndRetType(e, hs);
	this->parseParams(e, mthdstr.substr(bracket + 1, 
								mthdstr.length() - bracket - 2));

	int semicolon = Util::indexOf(rest, ';');
	int brace = Util::indexOf(rest, '{');
	if( string::npos != semicolon && 
			(string::npos == brace || semicolon < brace) ) {
		// pure virtual, like f() = 0;
		string ts = rest.substr(endbracket + 1, semicolon - endbracket - 1);
		e->PureVirtual = (ts.find('=', 0) != string::npos);

		idx0 += semicolon + 1;
	}
	else {
		int endbrace = Util::findMatching(rest, '{', '}');
		if( string::npos == endbrace )
			throw GenException("Can't find matching '{' and '}'", 
					Util::lineno(s, idx0));
		idx0 += endbrace + 1;
	}
	
	return e;
}

string MethodElmt::genWrapper4ECM(string classname)
{
	string methodname = this->getName();
	int paramnum = this->Parameters.size();
	ostringstream os;

	// only generate for constructor and creating method
	if( methodname != classname && 
			this->ReturnType[this->ReturnType.size()-1] != '*' )
		return os.str();

	
	os << "\tif( !method.compare(\"" + methodname + "\") && num == " <<
		paramnum << " )"	<< endl;

	if( methodname == classname ) {					// constructor
		os<<"\t\treturn (void*)(this->pBean = new " + methodname + "(";
	}
	else if( this->IsStatic &&						// static factory method
			Util::trimall(this->ReturnType) == (classname + "*") )	{
		os<<"\t\treturn (void*)(this->pBean = " + classname + 
			"::" + methodname + "(";
	}
	else if( this->IsStatic ) {						// static method
		os<<"\t\treturn (void*)(" + classname + "::" + methodname + "(";
	}
	else{
		os<<"\t\treturn (void*)(this->pBean->" + methodname + "(";
	}
	
	if( paramnum > 0 ){
		os << endl;
		int i;
		for( i=0; i<paramnum - 1; i++ ){
			os << "\t\t\t\t*(" + this->Parameters[i]->getType()
			   << "*)Prams[" <<i<< "],";
			os << endl;
		}
		os << "\t\t\t\t*(" + this->Parameters[i]->getType()
		   << "*)Prams[" <<i<< "]";

	}
	os << "));" << endl;

	return os.str();
}

string MethodElmt::genWrapper4EVM(string classname)
{
	string methodname = this->getName();
	int paramnum = this->Parameters.size();
	ostringstream os;

	// only generate for methods that return void
	if( this->ReturnType.compare("void") )
		return os.str();

	os << "if( !method.compare(\"" + methodname + "\") && num == " <<
		paramnum << " )"	<< endl;

	if( this->IsStatic ) {						// static method
		os<<"\t\t" + classname + "::" + methodname + "(";
	}
	else{
		os<<"\t\tthis->pBean->" + methodname + "(";
	}
	
	if( paramnum > 0 ){
		os << endl;
		int i;
		for( i=0; i<paramnum - 1; i++ ){
			os << "\t\t\t\t\t *(" + this->Parameters[i]->getType()
			   << "*)Prams[" <<i<< "],";
			os << endl;
		}
		os << "\t\t\t\t\t *(" + this->Parameters[i]->getType()
		   << "*)Prams[" <<i<< "]";

	}
	os << ");" << endl;
	os << "\telse ";

	return os.str();
}

string MethodElmt::genWrapper4GPT()
{
	string methodname = this->getName();
	int paramnum = this->Parameters.size();
	ostringstream os;

	if( '~' == methodname[0] )	// destructor
		return os.str();

	os << "if( !method.compare(\"" + this->getName() + "\") && num == " <<
		paramnum << " )"	<< endl;
	os<<"\t\ttypes = string(\"\")";
	
	if( paramnum > 0 ){
		for( int i=0; i<paramnum; i++){
			os << endl;
			os << "\t\t\t  + \"" 
			   << this->Parameters[i]->getType() + "|\"";
		}
	}
	os << ";" << endl;
	os << "\telse ";

	return os.str();
}

// s should has no comments
void MethodElmt::parseNameAndRetType(MethodElmt* e, string s)
{
	int idx;

	// is destructor
	if( string::npos != (idx = s.find('~', 0)) ){
		e->setName( Util::trimall(s.substr(idx)) );
		// destructor has no return type
		return;
	}

	// is overloading operator
	if( string::npos != (idx = s.find("operator", 0)) )
		e->setName( Util::trimall(s.substr(idx)) );
	else {	// is other
		string name = Util::getLastWord(s);
		e->setName(name);
		idx = Util::indexOf(s, name);
	}
	
	// parse return type
	string rt = s.substr(0, idx);
	vector<string>::iterator it = this->KnownAttrs.begin();
	for( ;it != this->KnownAttrs.end(); it++){
		if( string::npos != (idx = Util::indexOf(rt, *it)) )
			rt.erase(idx, it->length());
	}
	e->ReturnType = Util::trim(rt);
	
	return;
}

// s is the string between '(' and ')', and should has no comments.
void MethodElmt::parseParams(MethodElmt* e, string s)
{
	string rest = s;
	while( !rest.empty() ){
		// get a parameter's string
		int tempDepth = 0;	// Depth of template scope
		int idx = 0;
		while( idx < rest.length() && (rest[idx] != ',' || tempDepth > 0) ){
			if( rest[idx] == '=' ){
				// let idx skip literal string if has
				int l;
				string temps = rest.substr(idx + 1);
				if( l = Util::whiteSapceLen(temps) ){
					temps = temps.substr(l);
					idx += l;
				}
				if( l = Util::literalLen(temps) )
					idx += l;
			}
			else if( rest[idx] == '<' )
					tempDepth ++;
			else if( rest[idx] == '>' )
				tempDepth --;

			idx ++;
		}

		string pstr = Util::trim(rest.substr(0, idx));
		if( !pstr.empty() ){
			Parameter* p = new Parameter(pstr);
			if( !p->isVoid() )	// Copes with void func(void)
				e->Parameters.push_back(p);
			else
				delete p;
		}

		if( idx < rest.length() ) 
			rest = rest.substr(idx + 1);
		else
			break;
	}
}
