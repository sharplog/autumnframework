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
	this->TypeList.push_back((IAutumnType*)new BasicType<char, atoch, freech>(charBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<char, atoch, freech>(ucharBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<short, atosh, freesh>(shortBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<short, atosh, freesh>(ushortBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<int, atoint, freeint>(intBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<int, atoint, freeint>(uintBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<long, atolong, freelong>(longBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<unsigned long, atoul, freeul>(ulongBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<float, atofl, freefl>(floatBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<double, atodb, freedb>(doubleBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<charstrPointer, atocs, freecs>(cstrBT));
	this->TypeList.push_back((IAutumnType*)new BasicType<charstrPointer, atocs, freecs>(ucstrBT));
	this->TypeList.push_back((IAutumnType*)new StringType);

	// The following is for combined type.
	PointerType* ppt = new PointerType;
	ppt->setTypeManager(this);
	this->TypeList.push_back((IAutumnType*)ppt);
}

/** 
 * Destructor
 */
TypeManager::~TypeManager(){
	AutumnLog::getInstance()->debug("TypeManager->~TypeManager");
	for(vector<IAutumnType*>::iterator it = this->TypeList.begin(); it != this->TypeList.end(); it++){
		// customized type is freed by bean manager
		if( !this->isCustomized(it[0]) )
			delete it[0];
	}

	delete this->beanMaker;
}

IAutumnType* TypeManager::findTypeBean(string type)
{
	vector<IAutumnType*>::iterator tmp;
	for( tmp=this->TypeList.begin(); tmp!=this->TypeList.end(); tmp++){
		if( tmp[0]->isThisType(type) ){
			return tmp[0];
		}
	}

	AutumnLog::getInstance()->debug("TypeManager->findTypeBean: " + type);
	return this->beanMaker;
	
	throw new MissDefinitionEx("TypeManager", 
		"findTypeBean", 
		string("Type of [") + type + "] is not found!" );
}

void TypeManager::addCustomizedType(IAutumnType* p)
{
	this->CustomizedTypes.push_back(p);
}

bool TypeManager::isCustomized(IAutumnType* p)
{
	vector<IAutumnType*>::iterator tmp;
	for( tmp=this->CustomizedTypes.begin(); tmp!=this->CustomizedTypes.end(); tmp++){
		if( tmp[0] == p)
			return true;
	}
	return false;
}

void TypeManager::addTypeBean(string name, IAutumnType* at, bool customized)
{
	vector<IAutumnType*>::iterator tmp;
	for( tmp=this->TypeList.begin(); tmp!=this->TypeList.end(); tmp++){
		if( tmp[0] == at){
			this->TypeList.erase(tmp);
		}
	}

	this->TypeList.push_back(at);

	if( customized )
		this->addCustomizedType(at);
}
