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

/** 
 * Logger for AutumnFramework
 */
class AutumnLog{
private:
	/** the true logger */
	ILogAdapter * logger;

	/** The singleton's instance */
	static AutumnLog* instance;
	
	/** Constructor, logger is NULL */
	AutumnLog(const char* file = "");
	
public:
	/** Destructor */
	~AutumnLog(){
		if( this->logger ) 
			delete this->logger;
	}

	/** Get this singleton's instance */
	static AutumnLog* getInstance(){
		if( AutumnLog::instance == NULL)
			AutumnLog::instance = new AutumnLog();
		return AutumnLog::instance;
	}
	
	/** Set property logger */
	void setLogger(ILogAdapter* ilogger){
		if( this->logger ) 
			delete this->logger;

		this->logger = ilogger;
	}

	void debug(const string& msg){
		if( this->logger ) 
			this->logger->debug(msg);
	}

	void info(const string& msg){
		if( this->logger ) 
			this->logger->info(msg);
	}
	
	void warn(const string& msg){
		if( this->logger ) 
			this->logger->warn(msg);
	}
	
	void error(const string& msg){
		if( this->logger ) 
			this->logger->error(msg);
	}
	
	void fatal(const string& msg){
		if( this->logger ) 
			this->logger->fatal(msg);
	}
	
	void log(int level, const string& msg){
		if( this->logger ) 
			this->logger->log(level, msg);
	}
		
};

#endif
