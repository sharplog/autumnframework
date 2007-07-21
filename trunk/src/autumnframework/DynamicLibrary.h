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

#ifndef AUTUMN_DYNAMICLIBRARY_H
#define AUTUMN_DYNAMICLIBRARY_H

#include <string>
#include "Basic.h"
#include "AutumnException.h"
#include "ILibrary.h"

#ifdef WIN32
	#include <windows.h>

	#define _OPENDLL_(libname) LoadLibrary(libname)
	#define _GETFUNCTION_(libpoint,funname) GetProcAddress(libpoint, funname)
	#define _CLOSEDLL_(libpoint) FreeLibrary(libpoint)
	#define _DLLHANDLE_ HINSTANCE
#else
	#include <dlfcn.h>

	#define _OPENDLL_(libname) dlopen(libname, RTLD_LAZY)
	#define _GETFUNCTION_(libpoint,funname) dlsym(libpoint, funname)
	#define _CLOSEDLL_(libpoint) dlclose(libpoint)
	#define _DLLHANDLE_ void*
#endif


using namespace std;

namespace Autumn{

/** 
 * Dynamic library 
 * @version 0.1.0
 * @since 2006-12-16
 */

class DynamicLibrary: public ILibrary{
private:
	string Name;
	string Path;
	_DLLHANDLE_ Handle;

public:
	/** Constructor */
	DynamicLibrary(string name, string path):Name(name), Path(path){
		this->Handle = _OPENDLL_(path.c_str());
		if( this->Handle == NULL){
			throw NotFoundEx("DynamicLibrary", "DynamicLibrary", 
				"Library [" + path + "] not found!");
		}
	}

	/** Destructor */
	~DynamicLibrary(){
		AutumnLog::getInstance()->debug("DynamicLibrary->~DynamicLibrary");
		if( this->Handle != NULL )
			_CLOSEDLL_(this->Handle);
	}

	/** Get function address */
	void* getFunction(string name){
		void* p = _GETFUNCTION_(this->Handle, name.c_str());
		if( p )
			return p;
		throw NotFoundEx("DynamicLibrary", "getFunction", 
			"function [" + name + "] not found!");
	}
};

} // End namespace Autumn
#endif
