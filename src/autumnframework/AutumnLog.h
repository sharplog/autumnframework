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

#ifndef AUTUMN_AUTUMNLOG_H
#define AUTUMN_AUTUMNLOG_H

#include "ILogAdapter.h"
#include "IBeanWrapper.h"

namespace Autumn{

/** 
 * Logger for AutumnFramework
 */
class AutumnLog{
private:
	/** the true logger */
	ILogAdapter * Logger;

	/** the logger is default or not */
	bool isDefault;

	/** The singleton's instance */
	static AutumnLog* Instance;
	
	/** Constructor, logger is NULL */
	AutumnLog();
	
public:
	/** Destructor */
	~AutumnLog();

	/** Get this singleton's instance */
	static AutumnLog* getInstance();
	
	/** Set property logger from a bean*/
	void injectLogger(ILogAdapter* ilogger);

	/** Set property logger for default */
	void setDefaultLogger();

	void debug(const string& msg){
		if( this->Logger ) 
			this->Logger->debug(msg);
	}

	void info(const string& msg){
		if( this->Logger ) 
			this->Logger->info(msg);
	}
	
	void warn(const string& msg){
		if( this->Logger ) 
			this->Logger->warn(msg);
	}
	
	void error(const string& msg){
		if( this->Logger ) 
			this->Logger->error(msg);
	}
	
	void fatal(const string& msg){
		if( this->Logger ) 
			this->Logger->fatal(msg);
	}
	
	void log(int level, const string& msg){
		if( this->Logger ) 
			this->Logger->log(level, msg);
	}
		
};

} // End namespace Autumn

#endif
