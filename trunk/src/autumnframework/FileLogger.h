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

#ifndef AUTUMN_FILELOGGER_H
#define AUTUMN_FILELOGGER_H

#include <string>
#include <fstream>
#include "ILogAdapter.h"
#include "AutumnException.h"

using namespace std;

/** 
 * Adapter for external log implementation
 * @version 0.1.0
 * @since 2006-11-30
 */

class FileLogger: public ILogAdapter {
	/** Log level */
	ofstream Of;
	int Level;
public:
	FileLogger(string filepath, int level):Level(level){
		this->Of.open(filepath.c_str(), ios::out | ios::app);
		if( !this->Of.is_open() )
			throw new InitException("FileLogger", "FileLogger", 
				string("Can't open file[" + filepath + "]."));
	}
	
	void debug(const string& msg){
		this->log(0, "DEBUG: " + msg);
	}

	void info(const string& msg){
		this->log(1, "INFO: " + msg);
	}
	
	void warn(const string& msg){
		this->log(2, "WARN: " + msg);
	}
	
	void error(const string& msg){
		this->log(3, "ERROR: " + msg);
	}
	
	void fatal(const string& msg){
		this->log(4, "FATAL: " + msg);
	}
	
	void log(int level, const string& msg){
		if( level >= this->Level )
			this->Of<<msg<<endl;
	}
};
#endif
