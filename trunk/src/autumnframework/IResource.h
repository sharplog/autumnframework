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

#ifndef AUTUMN_IRESOURCE_H
#define AUTUMN_IRESOURCE_H

#include <vector>
#include "AutumnDefinition.h"

namespace Autumn{

/** 
 * Interface of configuration resource
 * @version 0.1.0
 * @since 2006-12-6
 */

class IResource{
public:
	/** 
	 * Destructor
	 */
	virtual ~IResource(){}

	/** Return all libraries configuration */
	virtual const vector<TLibrary*>* getLibraries() const = 0;
};

} // End namespace Autumn
#endif
