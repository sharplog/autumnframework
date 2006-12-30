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

#include "BeanConfig.h"

/** erase space char */
string trimString(const string v)
{
	string s=v;
	for(int i=0; i<s.size(); ){
		if( isspace(s.at(i)) ){
			s.erase(i,1);
		}
		else i++;
	}
	return s;
}


BeanConfig::BeanConfig(TBean& beandef, WrapperMaker* wc, WrapperFreer* wd)
{
	this->Name = beandef.Name;
	this->WrapperCreater = wc;
	this->WrapperDeleter = wd;
	this->Initializable = beandef.Initializable;
	this->Destroyable = beandef.Destroyable;
	this->DependedObjects = beandef.DependedObjects;
	this->Singleton = beandef.Singleton;
	
	this->ConArgs = new PropertyList;
	this->Properties = new PropertyList;
	
	int i;
	TProperty *p;
	for(i=0; i<beandef.ConArgs.size(); i++){
		p = &beandef.ConArgs.at(i);
		this->ConArgs->push_back(new BeanProperty(p->Name,
				trimString(p->Type), p->Value, p->Managed));
	}
	for(i=0; i<beandef.Properties.size(); i++){
		p = &beandef.Properties.at(i);
		auto_ptr<BeanProperty> pb(new BeanProperty(p->Name, 
				trimString(p->Type), p->Value, p->Managed));
		this->Properties->push_back(pb.release());
	}
}

BeanConfig::~BeanConfig()
{
	int i;
	for(i=0; i<this->ConArgs->size(); i++){
		delete this->ConArgs->at(i);
	}
	for(i=0; i<this->Properties->size(); i++){
		delete this->Properties->at(i);
	}
	delete this->ConArgs;
	delete this->Properties;	
}

IBeanWrapper* BeanConfig::createWrapper()
{
	IBeanWrapper* p = this->WrapperCreater();
	p->setInitializable(this->Initializable);
	p->setDestroyable(this->Destroyable);
	p->setWrapperDeleter(this->WrapperDeleter);

	return p;
}
