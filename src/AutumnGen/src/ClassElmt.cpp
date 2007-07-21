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
#include "Configuration.h"
#include "ElmtFactory.h"
#include "MethodElmt.h"
#include "DocCommentElmt.h"
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
	string basestr = rest.substr(0, brace);
	int colon = Util::indexOf(basestr, ':');
	if( colon == string::npos )
		e->setName( Util::getLastWord(basestr) );
	else {
		e->setName( Util::getLastWord(basestr.substr(0, colon)) );

		int comma = Util::indexOf(basestr, ',');
		while( comma != string::npos ){
			e->BaseClass.push_back( Util::getLastWord(basestr.substr(0, comma)) );
			basestr = basestr.substr(comma+1);
			comma = Util::indexOf(basestr, ',');
		}
		e->BaseClass.push_back( Util::getLastWord(basestr) );
	}

	// parsing class body
	int idx, ridx;
	idx = idx0 + brace + 1;
	string scope = "private";
	DocCommentElmt* dc = NULL;

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
				child->setScope(scope);
				e->addChild(child);

				// if child is a document comment
				if( child->getType() == IElement::DOCCOMMENT ){
					dc = (DocCommentElmt*)child;
				}
				else if( dc != NULL ) {
					child->associateComment(dc);
					dc = NULL;
				}
			}
		}
	}

	this->addDefaultCon(e);

	// modify idx0 only when successed
	idx0 = idx0 + endbrace + 1;
	return e;
}

string ClassElmt::genWrapperCPP()
{
	// abstract class needs a wrapper also.
	//if( this->isAbstract() )
	//	return "";

	ostringstream os;
	os <<
	"/**"													<< endl <<
	" * Wrapper methods for " << this->getName()			<< endl <<
	" */"													<< endl;
	os << this->genWrapper4ECM();
	os << this->genWrapper4EVM();
	os << this->genWrapper4GPT();
	os << this->genWrapper4Cast();
	os << this->genWrapperTail();
	os << this->genWrapperCPP4Local();

	return os.str();
}

string ClassElmt::genWrapperH()
{
	// abstract class needs a wrapper also.
	//if( this->isAbstract() )
	//	return "";

	string classname = this->getName();
	string wrappername = classname + Configuration::getCWS();
	ostringstream os;

	os <<
	"/**"													<< endl <<
	" * Wrapper for " << classname							<< endl <<
	" */"													<< endl <<
	"class " + wrappername + ": public Autumn::IBeanWrapper{"<< endl <<
	"	" + classname + "* pBean;"							<< endl <<
	""														<< endl <<
	"public: "												<< endl <<
	"	" + wrappername + "(){"								<< endl <<
	"		this->setBeanName(\"" + classname + "\");"		<< endl <<
	"		this->pBean = NULL;"							<< endl <<
	"	}"													<< endl <<
	""														<< endl <<
	"	~" + wrappername + "(){"							<< endl <<
	"		if( this->pBean && !this->deleteBean() )"		<< endl <<
	"			delete this->pBean;"						<< endl <<
	"	}"													<< endl <<
	""														<< endl <<
	"	void* getBean(){ return (void*)this->pBean; }"		<< endl <<
	"	void  setBean(void* p){"							<< endl <<
	"		this->pBean = (" + classname + "*)p;"			<< endl <<
	"	}"													<< endl <<
	""														<< endl <<
	"	void* execCreateMethod(string& method, void** Prams, int num);"<<endl<<
	""																<<endl<<
	"	int execVoidMethod(string& method, void** Prams, int num);"	<<endl<<
	""																<<endl<<
	"	int getParamTypes(string& method, string& types, int num);"	<<endl<<
	""																<<endl<<
	"	void* cast2Base(const string basename);"					<<endl<<
	""																<<endl<<
	"};"															<<endl<<
	""																<<endl<<
	"extern \"C\"{"													<<endl<<
	"	DLL_EXPORT Autumn::IBeanWrapper* create_" + wrappername + "();"<<endl<<
	"	DLL_EXPORT void delete_" + wrappername + "(Autumn::IBeanWrapper*);"<<endl<<
	"}"																<<endl<<
	""																<<endl;
	os << this->genWrapperH4Local();
	
	return os.str();
}

string ClassElmt::genWrapperTail()
{
	string wrappername = this->getName() + Configuration::getCWS();
	ostringstream os;

	os <<
	"extern \"C\"{"												<< endl <<
	"	Autumn::IBeanWrapper* create_" + wrappername + "(){"	<< endl <<
	"		return new " + wrappername + ";"					<< endl <<
	"	}"														<< endl <<
	"	void delete_" + wrappername + "(Autumn::IBeanWrapper* p){"<< endl <<
	"		delete p;"											<< endl <<
	"	}"														<< endl <<
	"}"															<< endl <<
	""															<< endl;

	return os.str();
}

string ClassElmt::genWrapper4ECM()
{
	vector<IElement*> children = this->getChildren();
	string wrappername = this->getName() + Configuration::getCWS();

	ostringstream os;
	os<<
	"void* "<< wrappername << "::" <<
	"execCreateMethod(string& method, void** Prams, int num)" << endl <<
	"{" <<endl;

	for( int i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD && e->getScope() == "public" ) {
			os << ((MethodElmt*)e)->genWrapper4ECM(this->getName());
		}
	}
	os					<< endl <<
	"	return NULL;"	<< endl <<
	"}"					<< endl <<
	""					<< endl;
	
	return os.str();
}

string ClassElmt::genWrapper4EVM()
{
	vector<IElement*> children = this->getChildren();
	string wrappername = this->getName() + Configuration::getCWS();

	ostringstream os;
	os<<
	"int "<< wrappername << "::" <<
	"execVoidMethod(string& method, void** Prams, int num)"	<<endl<<
	"{" <<endl<<
	"	";

	bool hasOut = false;
	for( int i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD && e->getScope() == "public" ) {
			string ws = ((MethodElmt*)e)->genWrapper4EVM(this->getName());
			if( !ws.empty() ){
				os << ws;
				hasOut = true;
			}
		}
	}

	if( hasOut )
		os						<< endl <<
		"		return -1;"		<< endl <<
		""						<< endl <<
		"	return 0;"			<< endl <<
		"}"						<< endl <<
		""						<< endl;
	else
		os <<
			"return -1;"		<< endl <<
		"}"						<< endl <<
		""						<< endl;

	return os.str();
}

string ClassElmt::genWrapper4GPT()
{
	vector<IElement*> children = this->getChildren();
	string wrappername = this->getName() + Configuration::getCWS();

	ostringstream os;
	os<<
	"int "<< wrappername << "::" <<
	"getParamTypes(string& method, string& types, int num)"	<<endl<<
	"{" <<endl<<
	"	";

	bool hasOut = false;
	for( int i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD && e->getScope() == "public" ) {
			string ws = ((MethodElmt*)e)->genWrapper4GPT();
			if( !ws.empty() ){
				os << ws;
				hasOut = true;
			}
		}
	}
	if( hasOut )
		os						<< endl <<
		"		return -1;"		<< endl <<
		""						<< endl <<
		"	return 0;"			<< endl <<
		"}"						<< endl <<
		""						<< endl;
	else
		os << 
			"return -1;"		<< endl <<
		"}"						<< endl <<
		""						<< endl;

	
	return os.str();
}

string ClassElmt::genWrapper4Cast()
{
	string wrappername = this->getName() + Configuration::getCWS();
	DocCommentElmt* dc = this->getComment();

	ostringstream os;
	os<<
	"void* "<< wrappername << "::" <<
	"cast2Base(const string basename)" << endl <<
	"{" <<endl;

	for( int i=0; i<this->BaseClass.size(); i++){
		string base = this->BaseClass[i];
		os << "	if( basename == \"" << base << "\" )" << endl <<
			  "		return (" << base << "*)(this->pBean);" << endl;
	}
	if( dc != NULL){
		vector<string> bv = dc->valueOfTag("base");
		for( int j=0; j<bv.size(); j++){
			os << "	if( basename == \"" << bv[j] << "\" )" << endl <<
				  "		return (" << bv[j] << "*)(this->pBean);" << endl;
	}

	}
	os							<< endl <<
	"	return this->pBean;"	<< endl <<
	"}"							<< endl <<
	""							<< endl;
	
	return os.str();
}

string ClassElmt::genWrapperCPP4Local()
{
	string wrappername = this->getName() + Configuration::getCWS();
	ostringstream os;

	os 
	<< "AUTUMN_" + wrappername + "_Local _AUTUMN_" + wrappername + "_Local_;"
	<< endl << endl;

	return os.str();
}

string ClassElmt::genWrapperH4Local()
{
	string wrappername = this->getName() + Configuration::getCWS();
	ostringstream os;

	os <<
	"class AUTUMN_" + wrappername + "_Local{"					<< endl <<
	"public:"													<< endl <<
	"	AUTUMN_" + wrappername + "_Local(){"					<< endl <<
	"		Autumn::registerLocalFunction("						<< endl <<
	"				\"create_" + wrappername + "\","			<< endl <<
	"				(void*)create_" + wrappername + ");"		<< endl <<
	"		Autumn::registerLocalFunction("						<< endl <<
	"				\"delete_" + wrappername + "\","			<< endl <<
	"				(void*)delete_" + wrappername + ");"		<< endl <<
	"	}"														<< endl <<
	"};"														<< endl <<
	""															<< endl;

	return os.str();
}

void ClassElmt::addDefaultCon(ClassElmt* c)
{
	// abstract class can't have constructor
	if( c->isAbstract() )
		return;

	vector<IElement*> children = c->getChildren();
	
	int i;
	for( i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD &&
				e->getName() == c->getName() ) {
			break;
		}
	}

	// add a default public constructor
	if( i >= children.size() ){
		MethodElmt* m = new MethodElmt;
		m->setName(c->getName());
		m->setScope(string("public"));
		c->addChild(m);
	}
}

bool ClassElmt::isAbstract()
{
	vector<IElement*> children = this->getChildren();
	
	for(int i=0; i<children.size(); i++){
		IElement* e = children[i];
		if( e->getType() == IElement::METHOD ) {
			if( ((MethodElmt*)e)->isPureVirtual() )
				return true;
		}
	}

	return false;
}

