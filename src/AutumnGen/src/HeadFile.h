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

#ifndef AUTUMN_HEADFILE_H
#define AUTUMN_HEADFILE_H

#include "IElement.h"

/** 
 * head file parsor 
 */
class HeadFile{

	/** head file's base name, not contain .h */
	string Basename;

	/** wrapper file's suffix behind base name */
	static string WrapperSuffix;

	/** output path */
	string OutPath;

	vector<IElement*> Elements;

	/** 
	 * read a head file into content
	 */
	void readFile(string infile, string& content);

	/** license information */
	static string licenseInfo();

	/** generate wrapper's .h file */
	void genWrapperH();

	/** generate wrapper's .cpp file */
	void genWrapperCPP();
	
public:
	HeadFile(string infile, string outpath = "");
	~HeadFile();

	/** 
	 * generate wrapper's .h file and .cpp file
	 */
	void genWrapper();

	/** for AOP, no implementation now */
	void genProxy(string outfile){}

	/** set wrapper file's suffix */
	void setWrapperSuffix(string s){
		HeadFile::WrapperSuffix = s;
	}
};

#endif

