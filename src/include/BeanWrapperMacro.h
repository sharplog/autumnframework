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
	~bean##_Wrapper(){												\
		if( this->pBean ) {											\
			if( this->Destroyable() ) {								\
				this->destroyBean();								\
			}														\
			if( this->hasDeletor() ) 								\
				this->deleteBean();									\
			else													\
				delete this->pBean;									\
		}															\
	}																\
																	\
	void* getBean(){ return (void*)this->pBean; }					\
	void  setBean(void* p){ this->pBean = (bean*)p; }

/** 
 * Create a bean with no or some arguments, get arguments' types
 * @param p The bean's construct arguments when creating bean, the first
 * argument is bean name or factory method name.
 * @param num The number of construct arguments
 * @param op Create bean or Get types of arguments.
 * @param args To return arguments' types.
 * @param pr To return created bean.
 * @return 0 if success, -1 if failed
 */
#define AUTUMNBEAN_CREATOR()										\
int operateCreator(string& ConMethod, void** p, int num,			\
						const char* op, string& args, void*& pr)	\
{

#define AUTUMNBEAN_CREATOR_END()									\
		return -1;													\
	return 0;														\
}

 /** 
 * Create a bean using constructor without argument.
 * @param bean The bean name, it is user's class name
*/
#define AUTUMNBEAN_CONSTRUCTOR(bean)								\
	if( ConMethod.compare(#bean) == 0 && num == 0 ){				\
		if( !strcmp(op, "create" ) )								\
			pr = this->pBean = new bean();							\
		else if ( !strcmp(op, "gettype") )							\
			args = "";												\
		else return -1;												\
	}																\
	else

/** 
 * Create a bean using constructor with arguments
 * @param bean The bean name, it is user's class name
 * @param type The argument's type
 */
#define AUTUMNBEAN_CONSTRUCTOR_1P(bean, type)						\
	if( ConMethod.compare(#bean) == 0 && num == 1 ){				\
		if( !strcmp(op, "create" ) )								\
			pr = this->pBean = new bean(*(type*)p[0]);				\
		else if ( !strcmp(op, "gettype") )							\
			args = #type "|";										\
		else return -1;												\
	}																\
	else

#define AUTUMNBEAN_CONSTRUCTOR_2P(bean, type1, type2)				\
	if( ConMethod.compare(#bean) == 0 && num == 2 ){				\
		if( !strcmp(op, "create" ) )								\
			pr = this->pBean = new bean(*(type1*)p[0],				\
										*(type2*)p[1]);				\
		else if ( !strcmp(op, "gettype") )							\
			args = #type1 "|" #type2 "|";							\
		else return -1;												\
	}																\
	else

#define AUTUMNBEAN_CONSTRUCTOR_13P(bean, type1, type2, type3, type4,\
								type5, type6, type7, type8, type9,	\
								type10, type11, type12, type13)		\
	if( ConMethod.compare(#bean) == 0 && num == 13 ){				\
		if( !strcmp(op, "create" ) )								\
			pr = this->pBean = new bean(*(type1*)p[0],				\
										*(type2*)p[1],				\
										*(type3*)p[2],				\
										*(type4*)p[3],				\
										*(type5*)p[4],				\
										*(type6*)p[5],				\
										*(type7*)p[6],				\
										*(type8*)p[7],				\
										*(type9*)p[8],				\
										*(type10*)p[9],				\
										*(type11*)p[10],			\
										*(type12*)p[11],			\
										*(type13*)p[12]);			\
		else if ( !strcmp(op, "gettype") )							\
			args = #type1 "|"  #type2 "|"  #type3 "|"				\
				   #type4 "|" #type5 "|"  #type6 "|"  #type7 "|"	\
				   #type8 "|" #type9 "|" #type10 "|" #type11 "|"	\
				   #type12 "|" #type13 "|";							\
		else return -1;												\
	}																\
else

 /** 
 * Create a bean with static factory method without argument
 * @param bean The bean name, it is user's class name
 * @param method The static factory method name
*/
#define AUTUMNBEAN_CON_METHOD(bean, method)							\
	if( ConMethod.compare(#method) == 0 && num == 0 ){				\
		if( !strcmp(op, "create" ) )								\
			pr = this->pBean = bean::method();						\
		else if ( !strcmp(op, "gettype") )							\
			args = "";												\
		else return -1;												\
	}																\
	else

/** 
 * Create a bean with static factory method with arguments
 * @param bean The bean name, it is user's class name
 * @param method The static factory method name
 * @param type The first parameter's type
 */
#define AUTUMNBEAN_CON_METHOD_1P(bean, method, type)				\
	if( ConMethod.compare(#method) == 0 && num == 1 ){				\
		if( !strcmp(op, "create" ) )								\
			pr = this->pBean = bean::method(*(type*)p[0]);			\
		else if ( !strcmp(op, "gettype") )							\
			args = #type "|";										\
		else return -1;												\
	}																\
	else

#define AUTUMNBEAN_CON_METHOD_2P(bean, method, type1, type2)		\
	if( ConMethod.compare(#method) == 0 && num == 2 ){				\
		if( !strcmp(op, "create" ) )								\
			pr = this->pBean = bean::method(*(type1*)p[0],			\
											*(type2*)p[1]);			\
		else if ( !strcmp(op, "gettype") )							\
			args = #type1 "|" #type2 "|";							\
		else return -1;												\
	}																\
	else

/** 
 * Create a product bean with factory without argument. This is used
 * in a factory bean's wrapper.
 * @param method The factory method name to make product.
*/
#define AUTUMNBEAN_CON_MAKER(method)								\
	if( ConMethod.compare(#method) == 0 && num == 0 ){				\
		if( !strcmp(op, "create" ) && this->pBean != NULL )			\
			pr = this->pBean->method();								\
		else if ( !strcmp(op, "gettype") )							\
			args = "";												\
		else return -1;												\
	}																\
	else

/** 
 * Create a product bean with factory with arguments. This is used
 * in a factory bean's wrapper.
 * @param method The factory method name
 * @param type The argument's type
 */
#define AUTUMNBEAN_CON_MAKER_1P(method, type)						\
	if( ConMethod.compare(#method) == 0 && num == 1 ){				\
		if( !strcmp(op, "create" ) && this->pBean != NULL )			\
			pr = this->pBean->method(*(type*)p[0]);					\
		else if ( !strcmp(op, "gettype") )							\
			args = #type "|";										\
		else return -1;												\
	}																\
	else

#define AUTUMNBEAN_CON_MAKER_2P(method, type1, type2)				\
	if( ConMethod.compare(#method) == 0 && num == 2 ){				\
		if( !strcmp(op, "create" ) && this->pBean != NULL )			\
			pr = this->pBean->method(*(type1*)p[0],	*(type2*)p[1]);	\
		else if ( !strcmp(op, "gettype") )							\
			args = #type1 "|" #type2 "|";							\
		else return -1;												\
	}																\
	else

 /** 
 * Initializing function
 * @param init The class's initializing function
 */
#define AUTUMNBEAN_INIT(init)										\
	bool Initializable(){ return true; }							\
	void initializeBean(){											\
		this->pBean->init();										\
	}
	
/** 
 * Initializing function
 * @param init The class's destroying function
 */
#define AUTUMNBEAN_DESTROY(destroy)									\
	bool Destroyable(){ return true; }								\
	void destroyBean(){												\
		this->pBean->destroy();										\
	}
	
/** 
 * bean's setter, the first part
 */
#define AUTUMNBEAN_SETTER()											\
	int operateBeanProperty(const char* name, const char* op, 		\
			string& type, void* value){

/** 
 * Add property
 * @param pname Property's name
 * @param ptype Property's type
 * @return 0 for success and -1 for failure
 */
#define AUTUMNBEAN_PROPERTY(pname, ptype)							\
		if( !strcmp(#pname, name) ){								\
			if( !strcmp(op, "setvalue")	)							\
				this->pBean->set##pname(*(ptype*)value);			\
			else if ( !strcmp(op, "gettype") )						\
				type = #ptype;										\
			else													\
				return -1;											\
		}															\
		else 

/** 
 * the last part of a bean's setter
 */
#define AUTUMNBEAN_SETTER_END()										\
			return -1;												\
		return 0;													\
	}
	
/** 
 * If a bean has deletor, must use it to delete the bean.
 * This maybe be usefule when a bean is created with static factory method.
 * @param bean The bean name, it is user's class name
 * @param method The deletor name
 */
#define AUTUMNBEAN_DELETOR(bean, method)							\
	bool hasDeletor(){return true;}									\
	void deleteBean(){												\
		bean::method(this->pBean);									\
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
	int operateCreator(string& ConMethod, void** p, int num,		\
						const char* op, string& args, void*& pr){	\
		if( num == 0 ){												\
			if( !strcmp(op, "create" ) )							\
				pr = this->pType = new type();						\
			else if ( !strcmp(op, "gettype") )						\
				args = "";											\
			else return -1;											\
		}															\
		else														\
			return -1;												\
		return 0;													\
	}																\
	~type##_Type(){													\
		if( this->pType )											\
			delete this->pType;										\
	}																\
	void* getBean(){ return (void*)this->pType; }					\
	void  setBean(void* p){ this->pType = (type*)p; }				\
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
