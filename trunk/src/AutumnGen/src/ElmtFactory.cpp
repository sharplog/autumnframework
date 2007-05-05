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

#include "ClassElmt.h"
#include "Enum_UnionElmt.h"
#include "FieldElmt.h"
#include "MethodElmt.h"
#include "NamespaceElmt.h"
#include "StructElmt.h"
#include "TypedefElmt.h"
#include "ElmtFactory.h"

ElmtFactory* ElmtFactory::instance = NULL;

ElmtFactory::ElmtFactory()
{
	this->Elements.push_back(new ClassElmt);
	this->Elements.push_back(new Enum_UnionElmt);
	this->Elements.push_back(new FieldElmt);
	this->Elements.push_back(new MethodElmt);
	this->Elements.push_back(new NamespaceElmt);
	this->Elements.push_back(new StructElmt);
	this->Elements.push_back(new TypedefElmt);
}

IElement* ElmtFactory::makeElmt(string& s, int& idx)
{
	if( ElmtFactory::instance == NULL )
		ElmtFactory::instance = new ElmtFactory;

	for(int i=0; i<ElmtFactory::instance->Elements.size(); i++){
		IElement* e = ElmtFactory::instance->Elements[i];
		if( e->isThisType(s, idx) )
			return e->clone(s, idx);
	}
	return NULL;
}

ElmtFactory::~ElmtFactory()
{
	for(int i=0; i<this->Elements.size(); i++)
		delete this->Elements[i];
}