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
#include <vector>
#include "IAutumnType.h"
#include "IBeanWrapper.h"

namespace Autumn{

	/** 
	 * Maintain all type makers.
	 * 
	 * @version 0.1.0
	 * @since 2006-11-25
	 */

	class TypeManager{
	private:
		/** Type makers */
		std::vector<IAutumnType*> TypeList;

		/** Type maker wrappers */
		std::vector<IBeanWrapper*> WrapperList;
		
		/** a type maker to create bean type value */
		IAutumnType* beanMaker;
	public:
		/** 
		 * Constructor, initialize the inline type
		 */
		TypeManager();

		/** 
		 * Destructor
		 */
		~TypeManager();
		
		/** 
		 * Set a AutumnType into list
		 * @param at A pointer to type maker
		*/
		void addTypeBean(IAutumnType* at);
		
		/** 
		 * Set a AutumnType and its wrapper into list
		 * @param pw Type maker's wrapper
		*/
		void addTypeBean(IBeanWrapper* pw);
		
		/** 
		 * find a type maker from list
		 * @param name Type name
		 */
		IAutumnType* findTypeBean(const std::string& name);

		void setBeanMaker(IAutumnType* p){
			this->beanMaker = p;
		}

	};

} // End namespace Autumn

#endif
