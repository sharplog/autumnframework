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

#include <memory>
#include <sstream>
#include "XMLResource.h"
#include "xmlParser.h"
#include "AutumnException.h"

/** 
 * Constructor, parse XML file 
 * @param path XML file path
 */
XMLResource::XMLResource(const char* path)
{
	XMLCSTR rootTag="autumn";
	XMLCSTR libTag="library";
	XMLResults errRlt;

	XMLNode rootNode = XMLNode::parseFile(path, rootTag, &errRlt);
	if( errRlt.error != eXMLErrorNone ){
		if( errRlt.error == eXMLErrorFileNotFound ){
			throw new XMLParsingEx("XMLResource", "XMLResource", 
				string("File not found: ") + path + ". ");
		}
		else{
			throw new XMLParsingEx("XMLResource", "XMLResource", 
				string("Error when parsing file '") + path + "'. " + 
				this->getErrorMsg(errRlt, rootTag));
		}
	}

	int i, pos=0, n = rootNode.nChildNode(libTag);
	for(i=0; i<n; i++){
		auto_ptr<TLibrary> plib(new TLibrary);
		XMLNode libNode = rootNode.getChildNode(libTag, &pos);
		this->parseLibrary(libNode, *plib);
		this->LibsConfig.push_back(plib.release());
	}
	if( n == 0)
		throw new XMLParsingEx("XMLResource", "XMLResource", 
			string("Error when parsing tag '") + libTag + 
			"'. There is no element '" + libTag + "'.");
}

/** Parse library */
void XMLResource::parseLibrary(XMLNode& xml, TLibrary& lib)
{
	XMLCSTR beanTag="bean";

	// parsing attributes
	XMLCSTR name = xml.getAttribute("name");
	XMLCSTR path = xml.getAttribute("path");
	XMLCSTR ns   = xml.getAttribute("namespace");

	if( name != NULL ) lib.Name = name;
	if( path != NULL ) lib.Path = path;
	if( ns   != NULL ) lib.NS   = ns;

	if( lib.Path.empty() ){
		throw new XMLParsingEx("XMLResource", "parseLibrary", 
			string("Error when parsing library '") + lib.Name + 
			"'. There is no path.");
	}

	if( lib.Name.empty() ){
		lib.Name = lib.Path;
	}
	
	// parsing beans
	int i, pos, n = 0;
	XMLNode beans = xml.getChildNode("beans");
	n= beans.nChildNode(beanTag);
	for( pos=0, i=0; i<n; i++ ){
		auto_ptr<TBean> pbean(new TBean);
		XMLNode beanNode = beans.getChildNode(beanTag, &pos);
		this->parseBean(beanNode, *pbean);
		lib.Beans.push_back(*pbean);
	}
	if( n==0 ){
		throw new XMLParsingEx("XMLResource", "parseLibrary", 
			string("Error when parsing tag '") + beanTag + 
			"'. There is no element '" + beanTag + "'.");
	}

	// parsing types, type is a bean.
	XMLNode types = xml.getChildNode("types");
	n = types.nChildNode(beanTag);
	for(pos=0, i=0; i<n; i++ ){
		auto_ptr<TBean> pbean(new TBean);
		XMLNode typeNode = types.getChildNode(beanTag, &pos);
		this->parseBean(typeNode, *pbean);
		lib.Beans.push_back(*pbean);
		lib.TypeNames.push_back(pbean->Name);
	}
}

/** Parse bean */
void XMLResource::parseBean(XMLNode& xml, TBean& bean)
{
	XMLCSTR propsTag="properties";
	XMLCSTR argsTag="constructor-arg";
	XMLCSTR dependTag="depends-on";
	
	// parsing attributes
	XMLCSTR name		= xml.getAttribute("name");
	XMLCSTR classname	= xml.getAttribute("class");
	XMLCSTR singleton	= xml.getAttribute("singleton");
	XMLCSTR factory		= xml.getAttribute("factory-bean");
	XMLCSTR factoryMthd	= xml.getAttribute("factory-method");
	XMLCSTR initMthd	= xml.getAttribute("init-method");
	XMLCSTR destroyMthd	= xml.getAttribute("destroy-method");
	XMLCSTR deleteMthd	= xml.getAttribute("delete-method");
	
	string isSingleton("false");
	
	if( name != NULL) bean.Name = name;
	if( classname != NULL ) bean.ClassName = classname;
	if( singleton != NULL ) isSingleton = singleton;
	if( factory != NULL ) bean.FactoryBean = factory;
	
	if( bean.ClassName.empty() ){
		throw new XMLParsingEx("XMLResource", "parseBean", 
			string("Error when parsing type '") + bean.Name + 
			"'. There is no class name.");
	}
	if( bean.Name.empty() ) bean.Name = bean.ClassName;
	if( factoryMthd != NULL ) bean.ConMethod = factoryMthd;
	else bean.ConMethod = bean.ClassName;

	if( initMthd != NULL ) bean.InitMethod = initMthd;
	if( destroyMthd != NULL ) bean.DestroyMethod = destroyMthd;
	if( deleteMthd != NULL ) bean.DeleteMethod = deleteMthd;

	bean.Singleton = this->boolAttribute(isSingleton, "singleton");
	
	// child node
	int i, pos, n;
	// Property
	XMLNode props = xml.getChildNode(propsTag);
	if( ! props.isEmpty() ){
		pos=0, n = props.nChildNode("property");
		for( i=0; i<n; i++ ){
			auto_ptr<TProperty> pprop(new TProperty);
			XMLNode proNode = props.getChildNode("property", &pos);
			this->parseProperty(proNode, *pprop, true);
			bean.Properties.push_back(*pprop);
		}
	}
	
	// Constructor argument
	XMLNode args = xml.getChildNode(argsTag);
	if( ! args.isEmpty() ){
		pos=0, n = args.nChildNode("argument");
		for( i=0; i<n; i++ ){
			auto_ptr<TProperty> parg(new TProperty);
			XMLNode argNode = args.getChildNode("argument", &pos);
			this->parseProperty(argNode, *parg, false);
			bean.ConArgs.push_back(*parg);
		}
	}
	
	// depends on bean
	XMLNode depends = xml.getChildNode(dependTag);
	if( ! depends.isEmpty() ){
		pos=0, n = depends.nChildNode("bean-name");
		for( i=0; i<n; i++ ){
			bean.DependedObjects.push_back(
				depends.getChildNode("bean-name", &pos).getText());
		}
	}
	
}

/* Parse Property */
void XMLResource::parseProperty(XMLNode& xml, TProperty& prop, bool isProp)
{
	// name
	XMLCSTR name = xml.getAttribute("name");
	if( name != NULL ) prop.Name = name;
	if( prop.Name.empty() && isProp == true ){
		throw new XMLParsingEx("XMLResource", "parseProperty", 
			"Error when parsing property. There is no property name.");
	}
	
	XMLCSTR type = xml.getAttribute("type");
	if( type != NULL ) prop.Type = type;

	prop.Managed = true;
	XMLCSTR managed = xml.getAttribute("autumn-manage");
	if( managed != NULL ) 
		prop.Managed = this->boolAttribute(managed, "autumn-manage");
	
	// values
	int	pos=0, n = xml.nChildNode("value");
	for( int i=0; i<n; i++ ){
		XMLCSTR v = xml.getChildNode("value", &pos).getText();
		if ( NULL == v)
			prop.Value.push_back("");
		else
			prop.Value.push_back(v);
	}

	// ref
	prop.IsBeanRef = false;
	XMLNode ref = xml.getChildNode("ref");
	if( ! ref.isEmpty() ){
		XMLCSTR b = ref.getAttribute("bean");
		if ( NULL != b){
			prop.Value.push_back(b);
			prop.IsBeanRef = true;
		}
		else{
			throw new XMLParsingEx("XMLResource", "parseProperty", 
				"Error when parsing property '" + prop.Name + 
				"'. There is no reference bean name .");
		}
	}
	
	if( n==0 && ref.isEmpty() ) {
		throw new XMLParsingEx("XMLResource", "parseProperty", 
			"Error when parsing property '" + prop.Name + 
			"'. There is no value.");
	}
}

/** Get parsing error message */
string XMLResource::getErrorMsg(XMLResults& err, const char* tag)
{
	ostringstream errStr;
	if( err.error != eXMLErrorNone) {
		errStr << "Error when parssing '" << tag << "'";
		if( err.nLine != 0 ){
			errStr << " at line " << err.nLine << ", column " << err.nColumn;
		}
		errStr << ".";
	}
	return errStr.str();
}

bool XMLResource::boolAttribute(string value, string name)
{
	if( value.compare("true") == 0 )
		return true;
	else if( value.compare("false") == 0 )
		return false;
	else{
		throw new XMLParsingEx("XMLResource", "boolAttribute", 
			"The value of '" + name + "' must be 'true' or 'false'.");
		// useless, only avoid some compiler to warn
		return true;
	}
}

