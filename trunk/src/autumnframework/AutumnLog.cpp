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

#include "AutumnLog.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

/**
 * Logger for AutumnFramework
 * 
 * @version 0.1.0
 * @since 2006-12-01
 */

AutumnLog* AutumnLog::Instance = NULL;
const string DefaultLogPath = "AutumnFramework.log";
const int DefaultLogLevel = 2;

AutumnLog::AutumnLog()
{
	this->Logger = NULL;
	this->isDefault = false;
	this->setDefaultLogger();
}

AutumnLog::~AutumnLog()
{
	if( this->isDefault) 
		delete this->Logger;
}

/** Get this singleton's instance */
AutumnLog* AutumnLog::getInstance()
{
	if( AutumnLog::Instance == NULL)
		AutumnLog::Instance = new AutumnLog();
	return AutumnLog::Instance;
}

/** Set property logger */
void AutumnLog::injectLogger(ILogAdapter* ilogger)
{
	if( this->isDefault ) delete this->Logger;
	this->Logger = ilogger;
	this->isDefault = false;
}

void AutumnLog::setDefaultLogger()
{
	if( ! this->isDefault ) {
		this->Logger = new FileLogger(DefaultLogPath, DefaultLogLevel);
		this->isDefault = true;
	}
}

