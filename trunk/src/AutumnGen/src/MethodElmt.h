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

#ifndef AUTUMN_METHODELMT_H
#define AUTUMN_METHODELMT_H

#include "IElement.h"
#include "Parameter.h"

/** 
 * Method element
 */
class MethodElmt: public IElement{
	/** the known attributes of member method */
	vector<string> KnownAttrs;

	vector<Parameter*> Parameters;

	/** 
	 * If a method has no return type and it's not a constructor, 
	 * it means returning a int.
	 */
	string ReturnType;

	bool IsStatic;

	bool IsVirtual;

	/** parse method name and return type */
	void parseNameAndRetType(string s);

	/** parse method parameter type*/
	void parseParams(string s);

public:
	/** constructor */
	MethodElmt();
	~MethodElmt(){
		for( int i=0; i<this->Parameters.size(); i++)
			delete this->Parameters[i];
	}
	
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

	/** 
	 * Generate wrapper part of this element.
	 * It's useless for method element.
	 */
	virtual string genWrapperPart(){
		return "";
	}

	/** Return the type of this element. */
	IElement::ElmtType getType(){
		return IElement::METHOD;
	}
	
	/** Generate wrapper part for execCreateMethod() */
	string genWrapper4ECM(string classname);

	/** Generate wrapper part for execVoidMethod() */
	string genWrapper4EVM(string classname);

	/** Generate wrapper part for getParamTypes() */
	string genWrapper4GPT();
};
#endif
