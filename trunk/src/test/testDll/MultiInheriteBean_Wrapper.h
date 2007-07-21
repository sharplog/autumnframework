/*
 * Generated by Autumn Generator.
 * 
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

#ifndef MULTIINHERITEBEAN_WRAPPER_H
#define MULTIINHERITEBEAN_WRAPPER_H

#include "IBeanWrapper.h"
#include "MultiInheriteBean.h"

/**
 * Wrapper for Base1
 */
class Base1_Wrapper: public Autumn::IBeanWrapper{
	Base1* pBean;

public: 
	Base1_Wrapper(){
		this->setBeanName("Base1");
		this->pBean = NULL;
	}

	~Base1_Wrapper(){
		if( this->pBean && !this->deleteBean() )
			delete this->pBean;
	}

	void* getBean(){ return (void*)this->pBean; }
	void  setBean(void* p){
		this->pBean = (Base1*)p;
	}

	void* execCreateMethod(string& method, void** Prams, int num);

	int execVoidMethod(string& method, void** Prams, int num);

	int getParamTypes(string& method, string& types, int num);

	void* cast2Base(const string basename);

};

extern "C"{
	DLL_EXPORT Autumn::IBeanWrapper* create_Base1_Wrapper();
	DLL_EXPORT void delete_Base1_Wrapper(Autumn::IBeanWrapper*);
}

class AUTUMN_Base1_Wrapper_Local{
public:
	AUTUMN_Base1_Wrapper_Local(){
		Autumn::registerLocalFunction(
				"create_Base1_Wrapper",
				(void*)create_Base1_Wrapper);
		Autumn::registerLocalFunction(
				"delete_Base1_Wrapper",
				(void*)delete_Base1_Wrapper);
	}
};

/**
 * Wrapper for Base2
 */
class Base2_Wrapper: public Autumn::IBeanWrapper{
	Base2* pBean;

public: 
	Base2_Wrapper(){
		this->setBeanName("Base2");
		this->pBean = NULL;
	}

	~Base2_Wrapper(){
		if( this->pBean && !this->deleteBean() )
			delete this->pBean;
	}

	void* getBean(){ return (void*)this->pBean; }
	void  setBean(void* p){
		this->pBean = (Base2*)p;
	}

	void* execCreateMethod(string& method, void** Prams, int num);

	int execVoidMethod(string& method, void** Prams, int num);

	int getParamTypes(string& method, string& types, int num);

	void* cast2Base(const string basename);

};

extern "C"{
	DLL_EXPORT Autumn::IBeanWrapper* create_Base2_Wrapper();
	DLL_EXPORT void delete_Base2_Wrapper(Autumn::IBeanWrapper*);
}

class AUTUMN_Base2_Wrapper_Local{
public:
	AUTUMN_Base2_Wrapper_Local(){
		Autumn::registerLocalFunction(
				"create_Base2_Wrapper",
				(void*)create_Base2_Wrapper);
		Autumn::registerLocalFunction(
				"delete_Base2_Wrapper",
				(void*)delete_Base2_Wrapper);
	}
};

/**
 * Wrapper for Multi_Base1
 */
class Multi_Base1_Wrapper: public Autumn::IBeanWrapper{
	Multi_Base1* pBean;

public: 
	Multi_Base1_Wrapper(){
		this->setBeanName("Multi_Base1");
		this->pBean = NULL;
	}

	~Multi_Base1_Wrapper(){
		if( this->pBean && !this->deleteBean() )
			delete this->pBean;
	}

	void* getBean(){ return (void*)this->pBean; }
	void  setBean(void* p){
		this->pBean = (Multi_Base1*)p;
	}

	void* execCreateMethod(string& method, void** Prams, int num);

	int execVoidMethod(string& method, void** Prams, int num);

	int getParamTypes(string& method, string& types, int num);

	void* cast2Base(const string basename);

};

extern "C"{
	DLL_EXPORT Autumn::IBeanWrapper* create_Multi_Base1_Wrapper();
	DLL_EXPORT void delete_Multi_Base1_Wrapper(Autumn::IBeanWrapper*);
}

class AUTUMN_Multi_Base1_Wrapper_Local{
public:
	AUTUMN_Multi_Base1_Wrapper_Local(){
		Autumn::registerLocalFunction(
				"create_Multi_Base1_Wrapper",
				(void*)create_Multi_Base1_Wrapper);
		Autumn::registerLocalFunction(
				"delete_Multi_Base1_Wrapper",
				(void*)delete_Multi_Base1_Wrapper);
	}
};

/**
 * Wrapper for Multi_Bean
 */
class Multi_Bean_Wrapper: public Autumn::IBeanWrapper{
	Multi_Bean* pBean;

public: 
	Multi_Bean_Wrapper(){
		this->setBeanName("Multi_Bean");
		this->pBean = NULL;
	}

	~Multi_Bean_Wrapper(){
		if( this->pBean && !this->deleteBean() )
			delete this->pBean;
	}

	void* getBean(){ return (void*)this->pBean; }
	void  setBean(void* p){
		this->pBean = (Multi_Bean*)p;
	}

	void* execCreateMethod(string& method, void** Prams, int num);

	int execVoidMethod(string& method, void** Prams, int num);

	int getParamTypes(string& method, string& types, int num);

	void* cast2Base(const string basename);

};

extern "C"{
	DLL_EXPORT Autumn::IBeanWrapper* create_Multi_Bean_Wrapper();
	DLL_EXPORT void delete_Multi_Bean_Wrapper(Autumn::IBeanWrapper*);
}

class AUTUMN_Multi_Bean_Wrapper_Local{
public:
	AUTUMN_Multi_Bean_Wrapper_Local(){
		Autumn::registerLocalFunction(
				"create_Multi_Bean_Wrapper",
				(void*)create_Multi_Bean_Wrapper);
		Autumn::registerLocalFunction(
				"delete_Multi_Bean_Wrapper",
				(void*)delete_Multi_Bean_Wrapper);
	}
};

/**
 * Wrapper for Multi_Base2
 */
class Multi_Base2_Wrapper: public Autumn::IBeanWrapper{
	Multi_Base2* pBean;

public: 
	Multi_Base2_Wrapper(){
		this->setBeanName("Multi_Base2");
		this->pBean = NULL;
	}

	~Multi_Base2_Wrapper(){
		if( this->pBean && !this->deleteBean() )
			delete this->pBean;
	}

	void* getBean(){ return (void*)this->pBean; }
	void  setBean(void* p){
		this->pBean = (Multi_Base2*)p;
	}

	void* execCreateMethod(string& method, void** Prams, int num);

	int execVoidMethod(string& method, void** Prams, int num);

	int getParamTypes(string& method, string& types, int num);

	void* cast2Base(const string basename);

};

extern "C"{
	DLL_EXPORT Autumn::IBeanWrapper* create_Multi_Base2_Wrapper();
	DLL_EXPORT void delete_Multi_Base2_Wrapper(Autumn::IBeanWrapper*);
}

class AUTUMN_Multi_Base2_Wrapper_Local{
public:
	AUTUMN_Multi_Base2_Wrapper_Local(){
		Autumn::registerLocalFunction(
				"create_Multi_Base2_Wrapper",
				(void*)create_Multi_Base2_Wrapper);
		Autumn::registerLocalFunction(
				"delete_Multi_Base2_Wrapper",
				(void*)delete_Multi_Base2_Wrapper);
	}
};

#endif
