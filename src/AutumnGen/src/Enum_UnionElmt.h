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

#ifndef AUTUMNGEN_ENUM_UNIONELMT_H
#define AUTUMNGEN_ENUM_UNIONELMT_H

#include "IElement.h"

/** 
 * enum and union element
 */
class Enum_UnionElmt: public IElement{

public:
	// !!! the following is not implemented now.!!!
	/** 
	 * The string is a element of this type or not.
	 * @param s the whole content of head file.
	 * @param idx Position to start parsing.
	 */
	virtual bool isThisType(const string& s, int idx){
		return false;
	}

	/** 
	 * Clone a element of this type from string s.
	 * @param s the whole content of head file.
	 * @param idx In: position to start parsing, 
	 *			  Out: the position after this element.
	 * !!Notice: if clone failed, idx should not be changed!
	 */
	virtual IElement* clone(const string& s, int& idx){
		return NULL;
	}

	/** Generate wrapper .h file part of this element */
	virtual string genWrapperH(){
		return "";
	}
	
	/** Generate wrapper .cpp file part of this element */
	virtual string genWrapperCPP(){
		return "";
	}

	/** Return the type of this element. */
	IElement::ElmtType getType() const {
		return IElement::ENUM_UNION;
	}
	
};
#endif
