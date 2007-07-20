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

#ifndef AUTUMNGEN_IELEMENT_H
#define AUTUMNGEN_IELEMENT_H

#include <string>
#include <vector>

using namespace std;

class DocCommentElmt;

/** 
 * interface of elements in c++ head file
 */
class IElement{
	/** name of this element. some elements may have no name. */
	string Name;

	/** 
	 * A comment for this element. 
	 * will be used for parsing @id for AOP, unused now.
	 */
	DocCommentElmt* Comment;

	/** this element's scope, public, protected or private */
	string Scope;

	/** children */
	vector<IElement*> ChildElmts;

public:
	/** Some element type in c++ head file, the others are ignored. */
	enum ElmtType{
		NAMESAPCE,
		CLASS,
		STRUCT,
		METHOD,
		FIELD,
		ENUM_UNION,
		TYPEDEF,
		DOCCOMMENT
	};

	IElement(){
		this->Comment = NULL;
	}

	/** 
	 * The string is a element of this type or not.
	 * @param s the whole content of head file.
	 * @param idx Position to start parsing.
	 */
	virtual bool isThisType(string& s, int idx) = 0;

	/** 
	 * Clone a element of this type from string s.
	 * @param s the whole content of head file.
	 * @param idx In: position to start parsing, 
	 *			  Out: the position after this element.
	 * !!Notice: if clone failed, idx should not be changed!
	 */
	virtual IElement* clone(string& s, int& idx) = 0;

	/** Return the type of this element. */
	virtual IElement::ElmtType getType() = 0;

	/** Generate wrapper .h file part of this element */
	virtual string genWrapperH() = 0;
	
	/** Generate wrapper .cpp file part of this element */
	virtual string genWrapperCPP() = 0;
	
	/** Associate a document comment with this element. */
	void associateComment(DocCommentElmt* comm){
		this->Comment = comm;
	}

	/** Get document comment of this element */
	DocCommentElmt* getComment(){
		return this->Comment;
	}
	
	/** Set the element's scope: public, protected or private. */
	void setScope(string scope){
		this->Scope = scope;
	}

	/** Get the element's scope: public, protected or private. */
	string getScope(){
		return this->Scope;
	}

	/** Set the name of this element. */
	void setName(string name){
		this->Name = name;
	}
	
	/** Return the name of this element. */
	string getName(){
		return this->Name;
	}

	/** Add a child element to this element */
	void addChild(IElement* e){
		this->ChildElmts.push_back(e);
	}

	/** Get all children */
	vector<IElement*> getChildren(){
		return this->ChildElmts;
	}

	virtual ~IElement(){
		for(int i=0; i<this->ChildElmts.size(); i++)
			delete this->ChildElmts[i];
	}
};

#endif

