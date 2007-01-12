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

#ifndef AUTUMN_ICOMBINEDTYPE_H
#define AUTUMN_ICOMBINEDTYPE_H

#include <vector>
#include <string>

using namespace std;

/** 
 * Interface of ValueType
 * 
 * @version 0.1.0
 * @since 2006-11-25
 */
class ICombinedType{
private:
	void* TypeMng;

protected:
	/** Create one value of basic type */
	void* createBasicValue(vector<string>& vl, string basicType);

	/** Free one value of basic type */
	void freeBasicValue(void* p, string basicType);
	
public:
	/** 
	 * Create a value from StrValueList.
	 * @param vl A Vector<string>
	 * @return A pointer to a pointer value
	 */
	virtual void* createValue(vector<string>& vl, string basicType) = 0;

	/** Free the space where p point, include it's memeber's space */
	virtual void freeValue(void* p, string basicType) = 0;
	
	/** Free the space where p point, don't free it's memeber's space */
	virtual void freeSelfSpace(void* p) = 0;
	
	/** 
	 * Set type manager
	 * use void* replacing TypeManager* for easy using, this interface becomes simpler.
	 * @param p A pointer to TypeManager
	 */
	void setTypeManager(void* p){
		this->TypeMng = p;
	}
	
	/** 
	 * Destructor
	 */
	virtual ~ICombinedType(){}
};

#endif
