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

#ifndef AUTUMN_WRAPPERMACRO_H
#define AUTUMN_WRAPPERMACRO_H

#include "IBeanWrapper.h"
#include <iostream>

#ifdef WIN32
	#ifdef _USRDLL
		#define DLL_EXPORT _declspec(dllexport)
	#else
		#define DLL_EXPORT 
	#endif
#else
	#define DLL_EXPORT
#endif

using namespace std;

/** Define a bean's adapter */
/** 
 * Define bean adapter's first part 
 * the constructor of adapter
 * the function to release bean
 * @param bean The bean name, it is user's class name
 */
#define AUTUMNBEAN(bean)											\
class bean##_Wrapper:public IBeanWrapper{							\
	bean * pBean;													\
																	\
public:																\
	bean##_Wrapper(){												\
		this->setBeanName(#bean);									\
		this->pBean = NULL;											\
	}																\
																	\
	~bean##_Wrapper(){											\
		if( this->pBean ) {											\
			if( this->getDestroyable() ) {							\
				this->destroyBean();								\
			}														\
			delete this->pBean;										\
		}															\
	}																\
																	\
	void* getBean(){ return (void*)this->pBean; }					\
																	\
	string trimString(const string v){								\
		string s=v;													\
		for(int i=0; i<s.size(); ){									\
			if( isspace(s.at(i)) ){									\
				s.erase(i,1);										\
			}														\
			else i++;												\
		}															\
		return s;													\
	}

/** 
 * Create a bean without parameter
 * @param bean The bean name, it is user's class name
 * @return NULL if failed
*/
#define AUTUMNBEAN_CONSTRUCTOR(bean)								\
	void* createBean(){												\
		this->pBean = NULL;											\
		this->pBean = new bean();									\
		return this->pBean;											\
	}

/** 
 * Create a bean with parameters
 * This is the first part of creating function.
 * @param bean The bean name, it is user's class name
 * @param param_num The number of constructor's parameters
 * @param type The first parameter's type
 * @return NULL if failed
 */
#define AUTUMNBEAN_CON_PARAMS(bean, param_num, type)				\
	void* createBean(void** pPrams, int num){						\
		this->pBean = NULL;											\
		if( num != param_num){										\
			return this->pBean;										\
		}															\
																	\
		int i = 0;												\
		this->pBean = new bean(										\
			*(type*)pPrams[i++]

/** 
 * Add the next parameter for constructor
 * @param type The parameter's type
 */
#define AUTUMNBEAN_CON_PARAM(type)									\
			,*(type*)pPrams[i++]

/** 
 * End of the parameter list and end of creating function
 */
#define AUTUMNBEAN_CON_PARAMS_END()									\
			);														\
																	\
		return this->pBean;											\
	}
	
/** 
 * Initializing function
 * @param init The class's initializing function
 */
#define AUTUMNBEAN_INIT(init)										\
	void initializeBean(){											\
		this->pBean->init();										\
	}
	
/** 
 * Initializing function
 * @param init The class's destroying function
 */
#define AUTUMNBEAN_DESTROY(destroy)									\
	void destroyBean(){												\
		this->pBean->destroy();										\
	}
	
/** 
 * bean's setter, the first part
 */
#define AUTUMNBEAN_SETTER()											\
	int setBeanProperty(const char* name,							\
			const char* type, void* value){

/** 
 * Add property
 * @param pname Property's name
 * @param ptype Property's type
 * @return 0 for success and -1 for failure
 */
#define AUTUMNBEAN_PROPERTY(pname, ptype)							\
		if(!strcmp(#pname, name) &&									\
				!this->trimString(#ptype).compare(type)){			\
			this->pBean->set##pname(*(ptype*)value);				\
		}															\
		else 
/** 
 * the last part of bean's setter
 */
#define AUTUMNBEAN_SETTER_END()										\
			return -1;												\
		return 0;													\
	}
	
/** 
 * the last part of bean adapter,
 * the creating function of bean adapter
 * @param bean The bean name, it is user's class name
 */
#define AUTUMNBEAN_END(bean)										\
};																	\
																	\
extern "C"{															\
	DLL_EXPORT IBeanWrapper* create_##bean##_Wrapper();				\
	DLL_EXPORT void delete_##bean##_Wrapper(IBeanWrapper*);			\
	IBeanWrapper* create_##bean##_Wrapper(){						\
		return new bean##_Wrapper;									\
	}																\
	void delete_##bean##_Wrapper(IBeanWrapper* p){					\
		delete p;													\
	}																\
}

/** 
 * Register creating function to local bean factory
 * @param bean The bean name, it is user's class name
 */
#define AUTUMN_LOCALBEAN(bean)										\
																	\
class AUTUMN_##bean##_Proxy{										\
private:															\
	string mangleName(string op, string objName){					\
		if( op == "create" )										\
			return "create_" + objName + "_Wrapper";				\
		else if( op == "delete" )									\
			return "delete_" + objName + "_Wrapper";				\
		else return string("");										\
	}																\
																	\
public:																\
	AUTUMN_##bean##_Proxy(){										\
		registerLocalFunction(										\
				this->mangleName("create", #bean).c_str(),			\
				(void*)create_##bean##_Wrapper);					\
		registerLocalFunction(										\
				this->mangleName("delete", #bean).c_str(),			\
				(void*)delete_##bean##_Wrapper);					\
	}																\
};																	\
																	\
AUTUMN_##bean##_Proxy _AUTUMN_##bean##_Proxy_;

/** 
 * Define a customized type wrapper, like bean wrapper
 * @param type the class devided from IBasicType or ICombinedType
 */
#define AUTUMNTYPE(type)											\
class type##_Type:public IBeanWrapper{								\
	type * pType;													\
																	\
public:																\
	type##_Type(){													\
		this->setBeanName(#type);									\
		this->pType = NULL;											\
	}																\
	void* createBean(){												\
		this->pType = NULL;											\
		this->pType = new type();									\
		return this->pType;											\
	}																\
	~type##_Type(){												\
		if( this->pType )											\
			delete this->pType;										\
	}																\
	void* getBean(){ return (void*)this->pType; }					\
};																	\
																	\
extern "C"{															\
	DLL_EXPORT IBeanWrapper* create_##type##_Type();				\
	DLL_EXPORT void delete_##type##_Type(IBeanWrapper*);			\
	IBeanWrapper* create_##type##_Type(){							\
		return new type##_Type;										\
	}																\
	void delete_##type##_Type(IBeanWrapper* p){						\
		delete p;													\
	}																\
}

#endif
