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
#include "ClassElmt.h"

bool ClassElmt::isThisType(string& s, int idx)
{
	string r = s.substr(idx);

	if( !Util::startWith(r, "class") )
		return false;

	int brace = Util::indexOf(r, '{');
	int semicolon = Util::indexOf(r, ';');

	return ( string::npos != brace && brace < semicolon );
}

IElement* ClassElmt::clone(string& s, int& idx0)
{
	// s is the whole content of head file
	string rest = s.substr(idx0);

	int brace = Util::indexOf(rest, '{');
	int endbrace = Util::findMatching(rest, '{', '}');
	if( string::npos == endbrace )
		throw GenException("Can't find matching '}' for class.", 
				Util::lineno(s, idx0));

	ClassElmt* e = new ClassElmt;

	// parsing name and base classes
	string basestr = rest.substr(0, brace-1);
	int colon = Util::indexOf(basestr, ':');
	if( colon == string::npos )
		e->setName( Util::getLastWord(basestr) );
	else {
		e->setName( Util::getLastWord(basestr.substr(0, colon-1)) );

		int comma = Util::indexOf(basestr, ',');
		while( comma != string::npos ){
			this->BaseClass.push_back( Util::getLastWord(basestr.substr(0, comma-1)) );
			basestr = basestr.substr(comma+1);
			comma = Util::indexOf(basestr, ',');
		}
		e->BaseClass.push_back( Util::getLastWord(basestr) );
	}

	// parsing class body
	int idx, ridx;
	idx = idx0 + brace + 1;
	string scope = "private";

	while( idx < idx0 + endbrace ){
		rest = s.substr(idx);

		if( ridx = Util::irrelevantLen(rest) ){
			idx += ridx;
		}
		else if( Util::startWith(rest, "private") ){
			scope = "private";
			idx += Util::indexOf(rest, ':') + 1; 
		}
		else if( Util::startWith(rest, "protected") ){
			scope = "protected";
			idx += Util::indexOf(rest, ':') + 1; 
		}
		else if( Util::startWith(rest, "public") ){
			scope = "public";
			idx += Util::indexOf(rest, ':') + 1; 
		}
		else{
			IElement* child = ElmtFactory::makeElmt(s, idx);
			if( child == NULL )
				idx += Util::unrecognisedLen(rest);
			else{
				e->addChild(child);
				e->setScope(scope);
			}
		}
	}
	// modify idx0 only when successed
	idx0 = idx0 + endbrace + 1;
	return e;
}

string ClassElmt::genWrapperPart()
{
	string ws = "";

	ws += this->genWrapperHead();
	ws += this->genWrapper4ECM();
	ws += this->genWrapper4EVM();
	ws += this->genWrapper4GPT();
	ws += this->genWrapperTail();

	return ws;
}

string ClassElmt::genWrapperHead()
{
	string classname = this->getName();
	string wrappername = classname + "_Wrapper";
	ostringstream os;

	os << 
	"class " + wrappername + ": public IBeanWrapper{"		<< endl <<
	"	" + classname + "* pBean;"							<< endl <<
	""														<< endl <<
	"public: "												<< endl <<
	"	" + wrappername + "(){"								<< endl <<
	"		this->setBeanName(\"" + classname + "\");"		<< endl <<
	"		this->pBean = NULL;"							<< endl <<
	"	}"													<< endl <<
	""														<< endl <<
	"	~" + wrappername + "(){"							<< endl <<
	"		if( this->pBean ) {"							<< endl <<
	"			string method = this->getDestroyMethod();"	<< endl <<
	"			if( !method.empty() )"						<< endl <<
	"				this->execVoidMethod(method, NULL, 0);"	<< endl <<
	"			method = this->getDeleteMethod();"			<< endl <<
	"			if( !method.empty() ) {"					<< endl <<
	"				void* p = this->pBean;"					<< endl <<
	"				this->execVoidMethod(method, &p, 1);"	<< endl <<
	"			}"											<< endl <<
	"			else"										<< endl <<
	"				delete this->pBean;"					<< endl <<
	"		}"												<< endl <<
	"	}"													<< endl <<
	""														<< endl <<
	"	void* getBean(){ return (void*)this->pBean; }"		<< endl <<
	"	void  setBean(void* p){"							<< endl <<
	"		this->pBean = (" + classname + "*)p;"			<< endl <<
	"	}"													<< endl <<
	""														<< endl;

	return os.str();
}

string ClassElmt::genWrapperTail()
{
	string wrappername = this->getName() + "_Wrapper";
	ostringstream os;

	os <<
	"};"														<< endl <<
	""															<< endl <<
	"extern \"C\"{"												<< endl <<
	"	DLL_EXPORT IBeanWrapper* create_" + wrappername + "();"	<< endl <<
	"	DLL_EXPORT void delete_" + wrappername + "(IBeanWrapper*);" << endl <<
	"	IBeanWrapper* create_" + wrappername + "(){"			<< endl <<
	"		return new " + wrappername + ";"					<< endl <<
	"	}"														<< endl <<
	"	void delete_" + wrappername + "(IBeanWrapper* p){"		<< endl <<
	"		delete p;"											<< endl <<
	"	}"														<< endl <<
	"}"															<< endl <<
	""															<< endl;

	return os.str();
}

string ClassElmt::genWrapper4ECM()
{
	int i;
	
	vector<IElement*> children = this->getChildren();

	for( i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD &&
				e->getName() == this->getName() ) {
			break;
		}
	}

	// add a default public constructor
	if( i == children.size() ){
		MethodElmt* m = new MethodElmt;
		m->setName(this->getName());
		m->setScope("public");
		this->addChild(m);
	}

	ostringstream os;
	os<<
	"	void* execCreateMethod(string& method, void** Prams, int num)" <<endl<<
	"	{"															   <<endl;

	for( i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD && e->getScope() == "public" ) {
			os << ((MethodElmt*)e)->genWrapper4ECM(this->getName());
		}
	}
	os<<
	"		return NULL;"	<<endl<<
	"	}"					<<endl<<
	""						<<endl;
	
	return os.str();
}

string ClassElmt::genWrapper4EVM()
{
	vector<IElement*> children = this->getChildren();

	ostringstream os;
	os<<
	"	int execVoidMethod(string& method, void** Prams, int num)"	<<endl<<
	"	{"															<<endl<<
	"		";

	for( int i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD && e->getScope() == "public" ) {
			os << ((MethodElmt*)e)->genWrapper4EVM(this->getName());
		}
	}
	os<<
	"			return -1;"		<< endl <<
	""							<< endl <<
	"		return 0;"			<< endl <<
	"	}"						<< endl <<
	""							<< endl;
	
	return os.str();
}

string ClassElmt::genWrapper4GPT()
{
	vector<IElement*> children = this->getChildren();

	ostringstream os;
	os<<
	"	int getParamTypes(string& method, string& types, int num)"	<<endl<<
	"	{"															<<endl<<
	"		";

	for( int i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD && e->getScope() == "public" ) {
			os << ((MethodElmt*)e)->genWrapper4GPT();
		}
	}
	os<<
	"			return -1;"		<< endl <<
	""							<< endl <<
	"		return 0;"			<< endl <<
	"	}"						<< endl <<
	""							<< endl;
	
	return os.str();
}

string ClassElmt::genWrapper4Local()
{
	string classname = this->getName();
	ostringstream os;

	os <<
	"class AUTUMN_" + classname + "_Proxy{"						<< endl <<
	"public:"													<< endl <<
	"	AUTUMN_" + classname + "_Proxy(){"						<< endl <<
	"		registerLocalFunction("								<< endl <<
	"				\"create_" + classname + "_Wrapper\","		<< endl <<
	"				(void*)create_" + classname + "_Wrapper);"	<< endl <<
	"		registerLocalFunction("								<< endl <<
	"				\"delete_" + classname + "_Wrapper\","		<< endl <<
	"				(void*)delete_" + classname + "_Wrapper);"	<< endl <<
	"	}"														<< endl <<
	"};"														<< endl <<
	""															<< endl <<
	"AUTUMN_" + classname + "_Proxy _AUTUMN_" + classname + "_Proxy_;" <<endl;

	return os.str();
}
