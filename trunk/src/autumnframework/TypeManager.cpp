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
#include <cstdlib>
#include "TypeManager.h"
#include "IAutumnType.h"
#include "BasicType.h"
#include "PointerType.h"
#include "ObjectType.h"
#include "StringType.h"
#include "AutumnException.h"

// The basic types
const string charBT("char");
const string ucharBT("unsignedchar");
const string shortBT("short");
const string ushortBT("unsignedshort");
const string intBT("int");
const string uintBT("unsignedint");
const string longBT("long");
const string ulongBT("unsignedlong");
const string floatBT("float");
const string doubleBT("double");
const string stringBT("string");
const string cstrBT("char*");
const string ucstrBT("unsignedchar*");

// The combined types
const string pointerCT("*");


/** 
 * The following global template and functions are for basic value type.
 */
typedef char* charstrPointer;

//return the first char, maybe lost the else.
char	atoch(const char* s){return s[0];}
short	atosh(const char* s){return (short)atoi(s);}
int		atoint(const char* s){return atoi(s);}
long	atolong(const char* s){return atol(s);}
unsigned long atoul(const char* s){return strtoul(s, NULL, 0);}
float	atofl(const char* s){return (float)atof(s);}
double	atodb(const char* s){return atof(s);}
charstrPointer atocs(const char* s){
	char* p = new char[strlen(s)+1];
	strcpy(p, s);
	return (charstrPointer)p;
}

void freech(char p){}
void freesh(short p){}
void freeint(int p){}
void freelong(long p){}
void freeul(unsigned long p){}
void freefl(float p){}
void freedb(double p){}
void freecs(charstrPointer p){
	delete p;
}

/** 
 * Constructor, initialize the basic type
 */
TypeManager::TypeManager()
{
	//I think that unsigned is same to singed to deal with except long
	// The following is for basic type.
	this->TypeList.insert(make_pair(charBT, (IAutumnType*)new BasicType<char, atoch, freech>));
	this->TypeList.insert(make_pair(ucharBT, (IAutumnType*)new BasicType<char, atoch, freech>));
	this->TypeList.insert(make_pair(shortBT, (IAutumnType*)new BasicType<short, atosh, freesh>));
	this->TypeList.insert(make_pair(ushortBT, (IAutumnType*)new BasicType<short, atosh, freesh>));
	this->TypeList.insert(make_pair(intBT, (IAutumnType*)new BasicType<int, atoint, freeint>));
	this->TypeList.insert(make_pair(uintBT, (IAutumnType*)new BasicType<int, atoint, freeint>));
	this->TypeList.insert(make_pair(longBT, (IAutumnType*)new BasicType<long, atolong, freelong>));
	this->TypeList.insert(make_pair(ulongBT, (IAutumnType*)new BasicType<unsigned long, atoul, freeul>));
	this->TypeList.insert(make_pair(floatBT, (IAutumnType*)new BasicType<float, atofl, freefl>));
	this->TypeList.insert(make_pair(doubleBT, (IAutumnType*)new BasicType<double, atodb, freedb>));
	this->TypeList.insert(make_pair(cstrBT, (IAutumnType*)new BasicType<charstrPointer, atocs, freecs>));
	this->TypeList.insert(make_pair(ucstrBT, (IAutumnType*)new BasicType<charstrPointer, atocs, freecs>));
	this->TypeList.insert(make_pair(stringBT, (IAutumnType*)new StringType));

	// The following is for combined type.
	PointerType* ppt = new PointerType;
	ppt->setTypeManager(this);
	this->TypeList.insert(make_pair(pointerCT, (IAutumnType*)ppt));
}

/** 
 * Destructor
 */
TypeManager::~TypeManager(){
	AutumnLog::getInstance()->debug("TypeManager->~TypeManager");
	for(map<string, IAutumnType*>::iterator it = this->TypeList.begin(); it != this->TypeList.end(); it++){
		// customized type is freed by bean manager
		if( !this->isCustomized(it->first) )
			delete it->second;
	}
}

IAutumnType* TypeManager::findTypeBean(string type)
{
	if( this->TypeList.find(type) != this->TypeList.end() ) {
		return this->TypeList[type];
	}
	
	for( int i=type.size()-1; i>0; i-- ){
		if( this->TypeList.find(type.substr(i)) != this->TypeList.end()){
			return this->TypeList[type.substr(i)];
		}
	}

	throw new MissDefinitionEx("TypeManager", 
		"findTypeBean", 
		string("Type of [") + type + "] is not found!" );
}

void TypeManager::addCustomizedType(string name)
{
	this->CustomizedTypes.push_back(name);
}

bool TypeManager::isCustomized(string type)
{
	vector<string>::iterator tmp;
	for( tmp=this->CustomizedTypes.begin(); tmp!=this->CustomizedTypes.end(); tmp++){
		if( tmp[0].compare(type) == 0)
			return true;
	}
	return false;
}

void TypeManager::addTypeBean(string name, IAutumnType* at, bool customized)
{
	if( this->TypeList.find(name) != this->TypeList.end() ){
		this->TypeList[name] = at;
	}
	else {
		this->TypeList.insert(make_pair(name, at));
	}
	if( customized )
		this->addCustomizedType(name);
}
