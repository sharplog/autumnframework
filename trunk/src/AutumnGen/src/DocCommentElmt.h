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

#ifndef AUTUMNGEN_DOCCOMMENT_H
#define AUTUMNGEN_DOCCOMMENT_H

#include <vector>
#include "IElement.h"
#include "Util.h"

using namespace std;

/** 
 * Document comment, the text between '/**' and '*'&'/'
 */
class DocCommentElmt: public IElement{

	/** the document comment string */
	string Comment;

public:
	DocCommentElmt(const string& s){
		this->Comment = s;
	}

	/** 
	 * The string is a element of this type or not.
	 * @param s the whole content of head file.
	 * @param idx Position to start parsing.
	 */
	virtual bool isThisType(const string& s, int idx){
		string r = s.substr(idx);
		return 0 != Util::DocCommentLen(r);
	}

	/** 
	 * Clone a element of this type from string s.
	 * @param s the whole content of head file.
	 * @param idx In: position to start parsing, 
	 *			  Out: the position after this element.
	 * @return If can't create, return NULL.
	 * !!Notice: if clone failed, idx should not be changed!
	 */
	virtual IElement* clone(const string& s, int& idx){
		string r = s.substr(idx);
		int len = Util::DocCommentLen(r);
		DocCommentElmt* dc = new DocCommentElmt(r.substr(0, len));
		idx += len;
		return dc;
	}

	/** Return the type of this element. */
	virtual IElement::ElmtType getType() const {
		return IElement::DOCCOMMENT;
	}

	/** Generate wrapper .h file part of this element */
	virtual string genWrapperH(){
		return "";
	}
	
	/** Generate wrapper .cpp file part of this element */
	virtual string genWrapperCPP(){
		return "";
	}
	
	/** 
	 * return the value of a tag, the words after @tagname.
	 * @param tag tag's name
	 */
	vector<string> valueOfTag(const string& tag);
};

#endif
