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

#ifndef AUTUMN_IBEANWRAPPER_H
#define AUTUMN_IBEANWRAPPER_H

#include <string>
#include <vector>
#include "Basic.h"

#ifdef WIN32
	#ifdef AUTUMNFRAMEWORK_EXPORTS
		#define DLL_IM_EXPORT _declspec(dllexport)
	#else
		#define DLL_IM_EXPORT _declspec(dllimport)
	#endif
	#ifdef _USRDLL
		#define DLL_EXPORT _declspec(dllexport)
	#else
		#define DLL_EXPORT 
	#endif
#else
	#define DLL_IM_EXPORT
	#define DLL_EXPORT 
#endif

using namespace std;

/** 
 * Wrapper of bean
 * 
 * @version 0.7.0
 * @since 2007-04-27
 */

class DLL_IM_EXPORT IBeanWrapper{
	typedef void WrapperFreer(IBeanWrapper*);
	
	/** bean name */
	string BeanName;

	/** pointers of parameters, using long type */
	vector<TPointer> Parameters;

	/** function pointer to delete wrapper */
	WrapperFreer* WrapperDeleter;

	/** 
	 * bean's property 
	 */
	bool Singleton;								// is singleton or not
	string InitMethod;							// init method name
	string DestroyMethod;						// destroy method name
	string DeleteMethod;						// destruct method name
	
public:
	virtual void* getBean() = 0;
	virtual void  setBean(void*) = 0;
	virtual void* execCreateMethod(string& method, void** pPrams, int num) = 0;
	virtual int   execVoidMethod(string& method, void** pPrams, int num) = 0;
	virtual int   getParamTypes (string& method, string& types, int num) = 0;
	
	string getConArgTypes(string& ConMethod, int num);
	
	void   setBeanName(string s){ this->BeanName = s; }
	string getBeanName(){ return this->BeanName; }
	
	void   setInitMethod(string s){ this->InitMethod = s; }
	string getInitMethod(){ return this->InitMethod; }
	
	void   setDestroyMethod(string s){ this->DestroyMethod = s; }
	string getDestroyMethod(){ return this->DestroyMethod; }
	
	void   setDeleteMethod(string s){ this->DeleteMethod = s; }
	string getDeleteMethod(){ return this->DeleteMethod; }
	
	void setSingleton(bool s){ this->Singleton = s; }
	bool getSingleton() { return this->Singleton; }

	void setWrapperDeleter(WrapperFreer* wd){ this->WrapperDeleter = wd; }
	WrapperFreer* getWrapperDeleter(){ return this->WrapperDeleter; }
	
	void addParameter(TPointer p){ this->Parameters.push_back(p); }
	vector<TPointer> getParameter(){ return this->Parameters; }

	int setBeanPropertyValue(const char* name, void* value){
		string method = string("set") + name;
		return this->execVoidMethod(method, &value, 1);
	}
	
	int getBeanPropertyType(const char* name, string& type);
	
	/** if has deleteMethod, use this to delete bean */
	bool deleteBean();
	
	/** Destructor */
	virtual ~IBeanWrapper();
};

/** register local function for local library */
DLL_IM_EXPORT void registerLocalFunction(const char* name, void* f);

#endif
