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

bool MethodElmt::isThisType(string& s, int idx)
{
	return false;
}

IElement* MethodElmt::clone(string& s, int& idx0)
{
	return NULL;
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

	
	os << "\t\tif( !method.compare(\"" + methodname + "\") && num == " <<
		paramnum << ")"	<< endl;

	if( methodname == classname ) {					// constructor
		os<<"\t\t\treturn this->pBean = new " + methodname + "(";
	}
	else if( this->IsStatic && 
			this->ReturnType == (classname + "*") )	{// static factory method
		os<<"\t\t\treturn this->pBean = " + classname + 
			"::" + methodname + "(";
	}
	else if( this->IsStatic ) {						// static method
		os<<"\t\t\treturn " + classname + "::" + methodname + "(";
	}
	else{
		os<<"\t\t\treturn this->pBean->" + methodname + "(";
	}
	
	if( paramnum > 0 ){
		os << endl;
		for( int i=0; i<paramnum - 1; i++){
			os << "\t\t\t\t\t*(" + this->Parameters[i] + "*)Prams[" <<i<< "],";
			os << endl;
		}
		os<<"\t\t\t\t\t*(" + this->Parameters[i] + "*)Prams[" <<i<< "]";

	}
	os << ");" << endl;

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
		paramnum << ")"	<< endl;

	if( this->IsStatic ) {						// static method
		os<<"\t\t\t" + classname + "::" + methodname + "(";
	}
	else{
		os<<"\t\t\tthis->pBean->" + methodname + "(";
	}
	
	if( paramnum > 0 ){
		os << endl;
		for( int i=0; i<paramnum - 1; i++){
			os << "\t\t\t\t\t*(" + this->Parameters[i] + "*)Prams[" <<i<< "],";
			os << endl;
		}
		os<<"\t\t\t\t\t*(" + this->Parameters[i] + "*)Prams[" <<i<< "]";

	}
	os << ");" << endl;
	os << "\t\telse ";

	return os.str();
}

string MethodElmt::genWrapper4GPT()
{
	int paramnum = this->Parameters.size();
	ostringstream os;

	os << "if( !method.compare(\"" + this->getName() + "\") && num == " <<
		paramnum << ")"	<< endl;
	os<<"\t\t\ttypes += \"\"";
	
	if( paramnum > 0 ){
		for( int i=0; i<paramnum - 1; i++){
			os << endl;
			os << "\t\t\t\t\t+ \"" + this->Parameters[i] + "|\"";
		}
	}
	os << ";" << endl;
	os << "\t\telse ";

	return os.str();
}