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

#ifndef AUTUMN_AUTUMNDEFINITION_H
#define AUTUMN_AUTUMNDEFINITION_H

#include <string>
#include <vector>
#include "Basic.h"

using namespace std;

/** struct to store property configuration */
typedef struct{
	string	Name;
	
	/** the initial type of property value */
	string	Type;
	
	/** the type is as when injecting */
	string	InjectType;
	
	StrValueList Value;	

	/** Property be managed by Autumn framework or not. */
	bool	Managed;
} TProperty;

/** struct to store bean configuration */
typedef struct{
	/** bean name */
	string	Name;

	/** POCO name */
	string	ClassName;

	/** POCO has intializing function or not */
	bool	Initializable;
	
	/** POCO has destroying function or not */
	bool	Destroyable;

	/** POCO as a singleton */
	bool	Singleton;

	/** POCO's properties to set */
	vector<TProperty> Properties;

	/** Use TProperty to save constructor arguments, set name as Arg_n. */
	vector<TProperty> ConArgs;

	/** Depended objects, should be singleton. */
	StrValueList DependedObjects;
} TBean;

/** struct to store customized type configuration */
typedef struct{
	/** Type name */
	string Name;

	/** Class derived from IBasicType or ICombinedType */
	string ClassName;

	/** Type is basic type or not. */
	bool IsBasic;
} TType;

/** struct to store library configuration */
typedef struct{
	/** Library's name. "local" is special for main program */
	string Name;

	/** Library file path. If name is "local", path is useless. */
	string Path;

	/** namespace for this library. not using it now */
	string NS;
	
	/** beans in library */
	vector<TBean> Beans;
	
	/** customized types */
	vector<TType> Types;
} TLibrary;

#endif
