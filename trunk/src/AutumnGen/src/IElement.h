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

#ifndef AUTUMN_IELEMENT_H
#define AUTUMN_IELEMENT_H

#include <string>

using namespace;

/** 
 * interface of elements in c++ head file
 */
class IElement{
	/** name of this element. some elements may have no name. */
	string Name;

	/** A comment for this element */
	string Comment;

	/** this element's scope, public, protected or private */
	string Scope;

public:
	/** Some element type in c++ head file, the others are ignored. */
	enum ElmtType{
		NAMESAPCE,
		CLASS,
		STRUCT,
		METHOD,
		FIELD,
		ENUM_UNION,
		TYPEDEF
	};

	/** 
	 * The string is a element of this type or not.
	 * @param s A part of head file.
	 */
	virtual bool isThisType(string& s) = 0;

	/** 
	 * Clone a element of this type from string s.
	 * @param s A part of head file.
	 */
	virtual IElement* clone(string& s) = 0;

	/** Return the type of this element. */
	ElmtType getType() = 0;

	/** Generate wrapper part of this element */
	string genWrapperPart() = 0;
	
	/** Set a comment for this element. */
	void setComment(string& comm){
		this->Comment = comm;
	}

	/** Get comment of this element */
	string getComment(){
		return this->Comment;
	}
	
	/** Set the element's scope: public, protected or private. */
	void setScope(string& scope){
		this->Scope = scope;
	}

	/** Get the element's scope: public, protected or private. */
	string getScope(string& scope){
		return this->Scope;
	}

	/** Set the name of this element. */
	void setName(string& name){
		this->Name = name;
	}
	
	/** Return the name of this element. */
	string getName(){
		return this->Name;
	}
};

#endif

