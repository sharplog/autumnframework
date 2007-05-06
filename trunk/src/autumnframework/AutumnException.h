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

#ifndef AUTUMN_EXCEPTION_H
#define AUTUMN_EXCEPTION_H

#include <exception>
#include <string>
#include "AutumnLog.h"

using namespace std;
/** 
 * The exceptions used in AutumnFramework
 * @version 0.1.0
 * @since 2006-11-30
 */

/**  
 * AutumnFramework's root exception
 */
class AutumnException: public exception{

	/** The class where exception happened. */
	string ClassName;

	/** The method where exception happened. */
	string MethodName;

	/** The cause of exception */
	string ErrMessage;

	/** whole message */
	string WholeMessage;

public:
	/** 
	 * Constructor with class name, method name and cause.
	 */
	AutumnException(string cname, string mname, string msg):
		ClassName(cname),MethodName(mname),ErrMessage(msg){

		this->WholeMessage = cname + "->" + mname + ": " + msg;
		AutumnLog::getInstance()->error(this->WholeMessage.c_str());
	}
	
	/** Destructor. Solaris need this */
	virtual ~AutumnException() throw() {}

	/** The method derived from system exception class */
	virtual const char* what() const throw(){
		return this->WholeMessage.c_str();
	}
};

/** Exception happened while initializing bean configuration*/
class InitException: public AutumnException{
public:
	InitException(string cname, string mname, string msg):
	  AutumnException(cname, mname, msg){
	  }

};

/** Exception happened while injecting beans */
class InjectionException: public AutumnException{
public:
	InjectionException(string cname, string mname, string msg):
	  AutumnException(cname, mname, msg){
	  }
};

/** Exception of not having something definition */
class MissDefinitionEx: public InitException{
public:
	MissDefinitionEx(string cname, string mname, string msg):
	  InitException(cname, mname, msg){
	  }
};

/** Exception of having non value */
class NonValueEx: public InitException{
public:
	NonValueEx(string cname, string mname, string msg):
	  InitException(cname, mname, msg){
	  }
};

/** Exception of having non instance */
class NonInstanceEx: public InitException{
public:
	NonInstanceEx(string cname, string mname, string msg):
	  InitException(cname, mname, msg){
	  }
};

/** Exception of not found the object operated on */
class NotFoundEx: public InitException{
public:
	NotFoundEx(string cname, string mname, string msg):
	  InitException(cname, mname, msg){
	  }
};

/** Reduplicate definition */
class ReduplicateEx: public InitException{
public:
	ReduplicateEx(string cname, string mname, string msg):
	  InitException(cname, mname, msg){
	  }
};

/** Parsing XML file error */
class XMLParsingEx: public InitException{
public:
	XMLParsingEx(string cname, string mname, string msg):
	  InitException(cname, mname, msg){
	  }
};

/** Create bean failed */
class CreateBeanFailedEx: public InjectionException{
public:
	CreateBeanFailedEx(string cname, string mname, string msg):
	  InjectionException(cname, mname, msg){
	  }
};

/** Create bean failed */
class SetPropertyFailedEx: public InjectionException{
public:
	SetPropertyFailedEx(string cname, string mname, string msg):
	  InjectionException(cname, mname, msg){
	  }
};
#endif

