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

#ifndef AUTUMN_NAMESPACEELMT_H
#define AUTUMN_NAMESPACEELMT_H

#include "IElement.h"

/** 
 * Namespace element
 */
class NamespaceElmt: public IElement{

	/** father namespace */
	string Supper;

public:
	/** 
	 * The string is a element of this type or not.
	 * @param s the whole content of head file.
	 * @param idx Position to start parsing.
	 */
	virtual bool isThisType(string& s, int idx);

	/** 
	 * Clone a element of this type from string s.
	 * @param s the whole content of head file.
	 * @param idx In: position to start parsing, 
	 *			  Out: the position after this element.
	 * !!Notice: if clone failed, idx should not be changed!
	 */
	virtual IElement* clone(string& s, int& idx);

	/** Generate wrapper .h file part of this element */
	virtual string genWrapperH();
	
	/** Generate wrapper .cpp file part of this element */
	virtual string genWrapperCPP();

	/** Return the type of this element. */
	IElement::ElmtType getType(){
		return IElement::NAMESAPCE;
	}
	
	/** set Supper */
	void setSupper(string s){
		this->Supper = s;
	}

	/** return Supper */
	string getSupper(){
		return this->Supper;
	}
};
#endif
