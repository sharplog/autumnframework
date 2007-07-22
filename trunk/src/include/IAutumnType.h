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

#ifndef AUTUMN_IAUTUMNTYPE_H
#define AUTUMN_IAUTUMNTYPE_H

#include <vector>
#include <string>

namespace Autumn{

	class TypeManager;

	/** 
	 * Interface of ValueType
	 * 
	 * @version 0.1.0
	 * @since 2006-11-25
	 */
	class IAutumnType{
	private:
		TypeManager* TypeMng;

	public:
		/** 
		 * Create a value from StrValueList.
		 * @param vl A Vector<string>
		 * @param it A iterator pointing to the first unused string, it will be changed
		 * in this function.
		 * @return A pointer to a pointer value
		 */
		virtual void* createValue(const std::string& type, 
			const std::vector<std::string>& vl, 
			std::vector<std::string>::iterator& it) = 0;

		/** Free the space where p point, include it's member's space */
		virtual void freeValue(void* p, const std::string& type) = 0;
		
		/** Free the space where p point, don't free it's member's space */
		virtual void freeSelfSpace(void* p) = 0;

		/** Is this type or not */
		virtual bool isThisType(const std::string& type) const = 0;
		
		/** 
		 * Set type manager
		 * @param p A pointer to TypeManager
		 */
		void setTypeManager(TypeManager* p){
			this->TypeMng = p;
		}
		
		TypeManager* getTypeManager() const {
			return this->TypeMng;
		}
		
		/** 
		 * Destructor
		 */
		virtual ~IAutumnType(){}
	};

} // End namespace Autumn

#endif
