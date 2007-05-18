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

#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include "HeadFile.h"
#include "Configuration.h"

using namespace std;

const string Version = "0.1.0";

void displayUsage()
{
	cout <<
	"Usage:"														  <<endl<<
	"AutumnGen [options] files"										  <<endl<<
	""																  <<endl<<
	"Options:"														  <<endl<<
	"-h             display this help message."						  <<endl<<
	"-v             display AutumnGen's version message."			  <<endl<<
	"-out <path>    output path to generate file. default is the same"<<endl<<
	"               as input file."									  <<endl<<
	"-hsuf <suffix> suffix of c++ head file, default is \".h\"."	  <<endl<<
	"-isuf <suffix> suffix of c++ implementation file, default is \".cpp\"."<<endl<<
	"-wsuf <suffix> the string appended to input file name, to compose"<<endl<<
	"               the output file name. default is \"_Wrapper\"."	  <<endl<<
	""																  <<endl;
}

void parseArgs(int& ac, char** av)
{
	map<string, string> configs;
	int i = 0;

	while( i < ac ){
		if( !strcmp(av[i], "-h") ){
			displayUsage();

			for(int j = i ; j + 1 < ac ; ++j)
				av[j] = av[j + 1];

			ac -= 1;
		}
		else if( !strcmp(av[i], "-v") ){
			cout <<"Autumn generator, version \"" << Version << "\"." << endl;

			for(int j = i ; j + 1 < ac ; ++j)
				av[j] = av[j + 1];

			ac -= 1;
		}
		else if( !strcmp(av[i], "-out")  ||
				 !strcmp(av[i], "-hsuf") ||
				 !strcmp(av[i], "-isuf") ||
				 !strcmp(av[i], "-wsuf") ){
			if( i + 1 >= ac ){
				cout << "AutumnGen: argument expected for some options!"<<endl;
				exit(1);
			}
			configs.insert(make_pair(string(av[i]), string(av[i+1])));

			for(int j = i ; j + 2 < ac ; ++j)
				av[j] = av[j + 2];

			ac -= 2;
		}
		else
			++i;
	}

	Configuration::setConfigs(configs);
}

int main(int argc, char** argv)
{
	if( argc == 1){
		displayUsage();
		return 0;
	}

	parseArgs(argc, argv);

	// argv[0] is the program name
	for( int i=1; i<argc; i++){
		HeadFile h(argv[i]);
		h.genWrapper();
	}
	
	return 0;
}
