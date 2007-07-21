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
#include "StringType.h"

namespace Autumn{

// The basic types
const string charAT("char");
const string ucharAT("unsignedchar");
const string shortAT("short");
const string ushortAT("unsignedshort");
const string intAT("int");
const string uintAT("unsignedint");
const string longAT("long");
const string ulongAT("unsignedlong");
const string floatAT("float");
const string doubleAT("double");
const string stringAT("string");
const string cstrAT("char*");
const string ucstrAT("unsignedchar*");
const string pointerAT("*");


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
 * Constructor, initialize the inline type
 */
TypeManager::TypeManager()
{
	//I think that unsigned is same to singed to deal with except long
	// The following is for basic type.
	this->TypeList.push_back( new BasicType<char, atoch, freech>(charAT) );
	this->TypeList.push_back( new BasicType<char, atoch, freech>(ucharAT) );
	this->TypeList.push_back( new BasicType<short, atosh, freesh>(shortAT) );
	this->TypeList.push_back( new BasicType<short, atosh, freesh>(ushortAT) );
	this->TypeList.push_back( new BasicType<int, atoint, freeint>(intAT) );
	this->TypeList.push_back( new BasicType<int, atoint, freeint>(uintAT) );
	this->TypeList.push_back( new BasicType<long, atolong, freelong>(longAT) );
	this->TypeList.push_back( new BasicType<unsigned long, atoul, freeul>(ulongAT) );
	this->TypeList.push_back( new BasicType<float, atofl, freefl>(floatAT) );
	this->TypeList.push_back( new BasicType<double, atodb, freedb>(doubleAT) );
	this->TypeList.push_back( new BasicType<charstrPointer, atocs, freecs>(cstrAT) );
	this->TypeList.push_back( new BasicType<charstrPointer, atocs, freecs>(ucstrAT) );
	this->TypeList.push_back( new StringType);

	PointerType* ppt = new PointerType;
	ppt->setTypeManager(this);
	this->TypeList.push_back( ppt );
}

/** 
 * Destructor
 */
TypeManager::~TypeManager(){
	AutumnLog::getInstance()->debug("TypeManager->~TypeManager");

	void (*pf)(IBeanWrapper*);
	vector<IAutumnType*>::iterator it;
	vector<IBeanWrapper*>::iterator itw;

	// delete wrappers, wrapper will delete type maker
	for(itw = this->WrapperList.begin(); itw != this->WrapperList.end(); itw++){
		for(it = this->TypeList.begin(); it != this->TypeList.end(); it++){
			if( *it == (*itw)->getBean() ) {
				this->TypeList.erase(it);
				break;
			}
		}
		pf = (*itw)->getWrapperDeleter();
		pf(*itw);
	}
	
	// delete inline type maker
	for(it = this->TypeList.begin(); it != this->TypeList.end(); it++){
			delete *it;
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
}

void TypeManager::addTypeBean(IAutumnType* at)
{
	vector<IAutumnType*>::iterator tmp;
	for( tmp=this->TypeList.begin(); tmp!=this->TypeList.end(); tmp++){
		if( tmp[0] == at){
			return;
		}
	}
	this->TypeList.push_back(at);
}

void TypeManager::addTypeBean(IBeanWrapper* pw)
{
	this->addTypeBean((IAutumnType*)pw->getBean());
	
	vector<IBeanWrapper*>::iterator tmp;
	for( tmp=this->WrapperList.begin(); tmp!=this->WrapperList.end(); tmp++){
		if( tmp[0] == pw){
			return;
		}
	}
	this->WrapperList.push_back(pw);
}

} // End namespace Autumn
