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
#else
	#define DLL_IM_EXPORT
#endif

using namespace std;

/** 
 * Wrapper of bean
 * 
 * @version 0.1.0
 * @since 2006-12-04
 */

class DLL_IM_EXPORT IBeanWrapper{
	typedef void WrapperFreer(IBeanWrapper*);
	
	string BeanName;

	/** pointers of parameters, using long type */
	vector<TPointer> Parameters;

	/** function pointer to delete wrapper */
	WrapperFreer* WrapperDeleter;

	/** 
	 * bean's property 
	 */
	bool Initializable;							// initializable or not
	bool Destroyable;							// destroyable or not
	bool Singleton;								// is singleton or not
	
public:
	virtual void* getBean() = 0;
	
	virtual bool hasDeletor(){return false;}	// has deletor or not

	void setBeanName(string name){ this->BeanName = name; }
	string getBeanName(){ return this->BeanName; }
	
	void setDestroyable(bool d){ this->Destroyable = d; }
	bool getDestroyable(){ return this->Destroyable; }
	
	void setInitializable(bool i){ this->Initializable = i; }
	bool getInitializable(){ return this->Initializable; }

	void setSingleton(bool s){ this->Singleton = s; }
	bool getSingleton() { return this->Singleton; }

	void setWrapperDeleter(WrapperFreer* wd){ this->WrapperDeleter = wd; }
	WrapperFreer* getWrapperDeleter(){ return this->WrapperDeleter; }
	
	void addParameter(TPointer p){ this->Parameters.push_back(p); }
	vector<TPointer> getParameter(){ return this->Parameters; }

	int setBeanPropertyValue(const char* name, void* value){
		string dummy;
		return this->operateBeanProperty(name, opSetPropValue, dummy, value);
	}
	
	int getBeanPropertyType(const char* name, string& type){
		return this->operateBeanProperty(name, opGetPropType, type, NULL);
	}
	
	
	string getConArgTypes(void** pPrams, int num);

	void* createBean(void** pPrams, int num);

	virtual void deleteBean();
	
	virtual void initializeBean();

	virtual void destroyBean();

	virtual int operateBeanProperty(const char* name, const char* op, string& type, void* value);
	
	virtual int operateCreator(void** p, int num, const char* op, string& args, void*& pr);
		
	/** Destructor */
	virtual ~IBeanWrapper();
};

/** register local function for local library */
DLL_IM_EXPORT void registerLocalFunction(const char* name, void* f);

#endif
