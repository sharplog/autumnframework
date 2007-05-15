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

#ifndef AUTUMNGEN_HEADFILE_H
#define AUTUMNGEN_HEADFILE_H

#include "IElement.h"

/** 
 * head file parsor 
 */
class HeadFile{

	/** the original file name */ 
	string filename;

	/** head file's base name, not contain .h */
	string Basename;

	/** output path */
	string OutPath;

	vector<IElement*> Elements;

	/** 
	 * read a head file into content
	 */
	void readFile(string infile, string& content);

	/** license information */
	static string licenseInfo();

	/** 
	 * generate wrapper's .h file.
	 * If has no .h file, don't generate .cpp file.
	 * @return 0, has generated a .h file, other value, has no .h file.
	 **/
	int genWrapperH();

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
};

#endif

