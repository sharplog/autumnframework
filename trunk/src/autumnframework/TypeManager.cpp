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
#include "BasicType.h"
#include "PointerType.h"
#include "ObjectType.h"
#include "StringType.h"
#include "TypeManager.h"
#include "AutumnException.h"

/** 
 * Maitain all ValueType
 * @version 0.1.0
 * @since 2006-11-25
 */

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
	char* p = (char*)malloc(strlen(s)+1);
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
	free(p);
}

/** global template and functions end. */


TypeManager* TypeManager::instance = NULL;

/** 
 * Constructor, initialize the basic type
 */
TypeManager::TypeManager()
{
	//I think that unsigned is same to singed to deal with except long
	// The following is for basic type.
	this->BasicTypeList.insert(make_pair(charBT, new BasicType<char, atoch, freech>));
	this->BasicTypeList.insert(make_pair(ucharBT, new BasicType<char, atoch, freech>));
	this->BasicTypeList.insert(make_pair(shortBT, new BasicType<short, atosh, freesh>));
	this->BasicTypeList.insert(make_pair(ushortBT, new BasicType<short, atosh, freesh>));
	this->BasicTypeList.insert(make_pair(intBT, new BasicType<int, atoint, freeint>));
	this->BasicTypeList.insert(make_pair(uintBT, new BasicType<int, atoint, freeint>));
	this->BasicTypeList.insert(make_pair(longBT, new BasicType<long, atolong, freelong>));
	this->BasicTypeList.insert(make_pair(ulongBT, new BasicType<unsigned long, atoul, freeul>));
	this->BasicTypeList.insert(make_pair(floatBT, new BasicType<float, atofl, freefl>));
	this->BasicTypeList.insert(make_pair(doubleBT, new BasicType<double, atodb, freedb>));
	this->BasicTypeList.insert(make_pair(cstrBT, new BasicType<charstrPointer, atocs, freecs>));
	this->BasicTypeList.insert(make_pair(ucstrBT, new BasicType<charstrPointer, atocs, freecs>));
	this->BasicTypeList.insert(make_pair(stringBT, new StringType));

	// The following is for combined type.
	this->CombinedTypeList.insert(make_pair(pointerCT, new PointerType));
}

/** 
 * Destructor
 */
TypeManager::~TypeManager(){
	for(map<string, IBasicType*>::iterator itb = this->BasicTypeList.begin(); itb != this->BasicTypeList.end(); itb++){
		delete itb->second;
	}
	for(map<string, ICombinedType*>::iterator itc = this->CombinedTypeList.begin(); itc != this->CombinedTypeList.end(); itc++){
		delete itc->second;
	}
}

IBasicType* TypeManager::findBasicType(string type)
{
	if( this->BasicTypeList.find(type) != this->BasicTypeList.end() ) {
		return this->BasicTypeList[type];
	}
	return NULL;
}

ICombinedType* TypeManager::findCombinedType(string type, int& pos)
{
	for( int i=type.size()-1; i>0; i-- ){
		if( this->CombinedTypeList.find(type.substr(i)) !=
			this->CombinedTypeList.end()){
			// type.substr(0, i) is basic type
			pos = i;
			return this->CombinedTypeList[type.substr(i)];
		}
	}
	return NULL;
}


/** Get this singleton's instance */
TypeManager* TypeManager::getInstance()
{
	if(TypeManager::instance == NULL) {
		TypeManager::instance = new TypeManager();
	}
	return TypeManager::instance;
}
 
/** 
 * Set a couple of name and BasicType into list
 * @param name Type name
 * @param bt A pointer to BasicType
*/
void TypeManager::setBasicType(string name, IBasicType* bt)
{
	if( this->BasicTypeList.find(name) != this->BasicTypeList.end() ){
		this->BasicTypeList[name] = bt;
	}
	else {
		this->BasicTypeList.insert(make_pair(name, bt));
	}
}

/** 
 * Set a couple of name and CombinedType into list
 * @param name Type name
 * @param ct A pointer to CombinedType
*/
void TypeManager::setCombinedType(string name, ICombinedType* ct)
{
	if( this->CombinedTypeList.find(name) != this->CombinedTypeList.end() ){
		this->CombinedTypeList[name] = ct;
	}
	else {
		this->CombinedTypeList.insert(make_pair(name, ct));
	}
}

/** 
 * Create a value from StrValueList.
 * @param vl A Vector<string>
 * @return A pointer to a value
 */
void* TypeManager::createValue(StrValueList& vl, string type)
{
	if( vl.size() == 0 ){
		throw new NonValueEx("TypeManager", 
			"createValue", 
			string("String value of type[") + type + string("] is not found!"));
	}
	
	if( IBasicType* bt = this->findBasicType(type) ) {
		return bt->createValue(vl);
	}

	int pos;
	if( ICombinedType* ct = this->findCombinedType(type, pos) ){
		return ct->createValue(vl, type.substr(0,pos));
	}

	throw new MissDefinitionEx("TypeManager", 
			"createValue", 
			string("Type of [") + type + string("] is not found!") );
}

/** Free the space where p point */
void TypeManager::freeValue(void* p, string type)
{
	AutumnLog::getInstance()->debug("TypeManager->freeValue, type: " + type);
	
	if( IBasicType* bt = this->findBasicType(type) ) {
		bt->freeValue(p);
		return;
	}
	
	int pos;
	if( ICombinedType* ct = this->findCombinedType(type, pos) ){
		ct->freeValue(p, type.substr(0,pos));
		return;
	}
	
	throw new MissDefinitionEx("TypeManager", 
		"freeValue", 
		string("Type of [") + type + string("] is not found!") );
}

/** Free the space where p pointing to, the space occupied by the type self */
void TypeManager::freeSelfSpace(void* p, string type)
{
	if( IBasicType* bt = this->findBasicType(type) ) {
		bt->freeValue(p);
		return;
	}
	
	int pos;
	if( ICombinedType* ct = this->findCombinedType(type, pos) ){
		ct->freeSelfSpace(p);
		return;
	}

	throw new MissDefinitionEx("TypeManager", 
		"freeSelfSpace", 
		string("Type of [") + type + string("] is not found!") );
}

/** 
 * Erase a couple of name and ValueType from list
 * @param type Type name
 */
void TypeManager::eraseValueType(string type)
{
	// the type maybe be in BasicTypeList or CombinedTypeList
	this->BasicTypeList.erase(type);
	this->CombinedTypeList.erase(type);
}
