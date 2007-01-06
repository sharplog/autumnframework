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

#if(defined WIN32 && defined _USRDLL)
	#define DLLEXPORT _declspec(dllexport)
	#define DLLIMPORT _declspec(dllimport)
#else
	#define DLLEXPORT 
	#define DLLIMPORT
#endif

using namespace std;

/** 
 * Wrapper of bean
 * 
 * @version 0.1.0
 * @since 2006-12-04
 */

class DLLEXPORT IBeanWrapper{
	typedef void WrapperFreer(IBeanWrapper*);
	typedef long ParamPointer;
	
	string BeanName;

	/** pointers of parameters, using long type */
	vector<ParamPointer> Parameters;
	WrapperFreer* WrapperDeleter;
	bool Initializable;
	bool Destroyable;
public:
	virtual void* getBean() = 0;

	void setBeanName(string name){
		this->BeanName = name;
	}

	string getBeanName(){
		return this->BeanName;
	}
	
	void setDestroyable(bool d){
		this->Destroyable = d;
	}
	
	bool getDestroyable(){
		return this->Destroyable;
	}
	
	void setInitializable(bool i){
		this->Initializable = i;
	}
	
	bool getInitializable(){
		return this->Initializable;
	}

	void addParameter(ParamPointer p){
		this->Parameters.push_back(p);
	}

	vector<ParamPointer> getParameter(){
		return this->Parameters;
	}
	
	virtual void* createBean();

	virtual void* createBean(void** pPrams, int num);

	virtual void initializeBean();

	virtual void destroyBean();

	virtual int setBeanProperty(const char* name, const char* type, void* value);

	void setWrapperDeleter(WrapperFreer* wd){
		this->WrapperDeleter = wd;
	}

	WrapperFreer* getWrapperDeleter(){
		return this->WrapperDeleter;
	}
	
	/** 
	 * Destructor
	 */
	virtual ~IBeanWrapper();
};

#endif
