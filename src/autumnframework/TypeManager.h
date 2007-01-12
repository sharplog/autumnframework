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

#ifndef AUTUMN_TYPEMANAGER_H
#define AUTUMN_TYPEMANAGER_H

#include <string>
#include <map>
#include "Basic.h"
#include "IBasicType.h"
#include "ICombinedType.h"

/** 
 * Maitain all ValueType, this is a singleton.
 * 
 * @version 0.1.0
 * @since 2006-11-25
 */

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

class TypeManager{
private:
	
	/** 
	 * Basic ValueTypes 
	 * @param string Basic ValueType's name
	 */
	map<string, IBasicType*> BasicTypeList;

	/** 
	 * Combined ValueTypes
	 * @param string Combined ValueType's postfix
	 */
	map<string, ICombinedType*> CombinedTypeList;

	/** Customized types */
	vector<string> CustomizedTypes;
	
	/** The singleton's instance */
	static TypeManager* instance;
	
	/** 
	 * Constructor, initialize the basic and combined type
	 */
	TypeManager();

	/** 
	 * Destructor
	 */
	~TypeManager();

	IBasicType* findBasicType(string type);

	ICombinedType* findCombinedType(string type, int& pos);

	/** a type is customized or not */
	bool isCustomized(string type);

	void addCustomizedType(string name);
	void eraseCustomizedType(string name);
	
public:
	/** Get this singleton's instance */
	static TypeManager* getInstance();
	
	/** 
	 * Get a ValueType according type name
	 * @param name Type name
	 * @return A pointer to a ValueType
	IBasicType* getBasicType(string name);
	*/
	
	/** 
	 * Get a ValueType according type name
	 * @param name Type name
	 * @return A pointer to a ValueType
	ICombinedType* getCombinedType(string name);
	*/
	
	/** 
	 * Set a couple of name and BasicType into list
	 * @param name Type name
	 * @param bt A pointer to BasicType
	*/
	void setBasicType(string name, IBasicType* bt, bool customized = false);
	
	/** 
	 * Set a couple of name and CombinedType into list
	 * @param name Type name
	 * @param ct A pointer to CombinedType
	*/
	void setCombinedType(string name, ICombinedType* ct, bool customized = false);
	
	/** 
	 * Erase a couple of name and ValueType from list
	 * @param name Type name
	 */
	void eraseValueType(string name, bool customized = false);

	/** 
	 * Create a value from StrValueList.
	 * @param vl A Vector<string>
	 * @return A pointer to a value
	 */
	void* createValue(StrValueList& vl, string type);

	/** Free the space where p pointing to */
	void freeValue(void* p, string type);

	/** Free the space where p pointing to, the space occupied by the type self */
	void freeSelfSpace(void* p, string type);
};

#endif
