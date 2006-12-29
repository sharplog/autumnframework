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

#include <sstream>
#include "XMLResource.h"
#include "xmlParser.h"
#include "AutumnException.h"

/** 
 * Parse XML configuration file
 * @version 0.1.0
 * @since 2006-12-18
 */

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
		throw new XMLParsingEx("XMLResource", "XMLResource", 
			string("Error when parsing file '") + path + "'. " + 
			this->getErrorMsg(errRlt, rootTag));
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
	XMLCSTR typeTag="type";

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

	// parsing beans
	int i, pos=0, n = xml.nChildNode(beanTag);
	for( i=0; i<n; i++ ){
		auto_ptr<TBean> pbean(new TBean);
		XMLNode beanNode = xml.getChildNode(beanTag, &pos);
		this->parseBean(beanNode, *pbean);
		lib.Beans.push_back(*pbean);
	}
	if( n==0 ){
		throw new XMLParsingEx("XMLResource", "parseLibrary", 
			string("Error when parsing tag '") + beanTag + 
			"'. There is no element '" + beanTag + "'.");
	}

	// parsing types
	pos=0, n = xml.nChildNode(typeTag);
	for( i=0; i<n; i++ ){
		auto_ptr<TType> ptype(new TType);
		XMLNode typeNode = xml.getChildNode(typeTag, &pos);
		this->parseType(typeNode, *ptype);
		lib.Types.push_back(*ptype);
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
	XMLCSTR init		= xml.getAttribute("initializable");
	XMLCSTR destory		= xml.getAttribute("destroyable");
	XMLCSTR singleton	= xml.getAttribute("singleton");
	
	string hasInit("false");
	string hasDestroy("false");
	string isSingleton("false");
	
	if( name != NULL) bean.Name = name;
	if( classname != NULL )bean.ClassName = classname;
	if( init != NULL ) hasInit = init;
	if( destory != NULL ) hasDestroy = destory;
	if( singleton != NULL ) isSingleton = singleton;

	if( bean.ClassName.empty() ){
		throw new XMLParsingEx("XMLResource", "parseBean", 
			string("Error when parsing type '") + bean.Name + 
			"'. There is no class name.");
	}
	if( bean.Name.empty() ){
		bean.Name = bean.ClassName;
	}

	bean.Initializable = this->boolAttribute(hasInit, "initializable");
	bean.Destroyable = this->boolAttribute(hasDestroy, "destroyable");
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
			this->parseProperty(proNode, *pprop);
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
			this->parseProperty(argNode, *parg);
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

/** Parse type */
void XMLResource::parseType(XMLNode& xml, TType& type)
{
	// parsing attributes
	XMLCSTR name = xml.getAttribute("name");
	XMLCSTR classname = xml.getAttribute("class");
	XMLCSTR basic = xml.getAttribute("basic");
	string isBasic("true");			// true in default

	if( name	  != NULL ) type.Name = name;
	if( classname != NULL ) type.ClassName = classname;
	if( basic	  != NULL ) isBasic = basic;
	
	if( type.ClassName.empty()){
		throw new XMLParsingEx("XMLResource", "parseType", 
			string("Error when parsing type '") + type.Name + 
			"'. There is no class name.");
	}
	
	if( type.Name.empty() )
		type.Name = type.ClassName;
	
	type.IsBasic = this->boolAttribute(isBasic, "basic");
}

/* Parse Property */
void XMLResource::parseProperty(XMLNode& xml, TProperty& prop)
{
	XMLCSTR valueTag="value";
	
	// parsing attributes
	XMLCSTR name = xml.getAttribute("name");
	XMLCSTR type = xml.getAttribute("type");
	XMLCSTR managed = xml.getAttribute("autumn-manage");
	string isManaged = "true";

	if( name != NULL ) prop.Name = name;
	if( type != NULL ) prop.Type = type;
	if( managed != NULL ) isManaged = managed;
	
	if( prop.Name.empty() ){
		throw new XMLParsingEx("XMLResource", "parseProperty", 
			"Error when parsing property. There is no property name.");
	}
	
	if( prop.Type.empty() ){
		throw new XMLParsingEx("XMLResource", "parseProperty", 
			"Error when parsing property. There is no property type.");
	}
	prop.Managed = this->boolAttribute(isManaged, "autumn-manage");
	
	// values
	int	pos=0, n = xml.nChildNode("value");
	for( int i=0; i<n; i++ ){
		prop.Value.push_back(
			xml.getChildNode("value", &pos).getText());
	}
	if( n==0 ){
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

