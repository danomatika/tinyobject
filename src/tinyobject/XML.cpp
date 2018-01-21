/*==============================================================================

	XML.cpp
	
	tinyobject: object-based xml classes for TinyXml-2
  
	Copyright (C) 2009, 2010 Dan Wilcox <danomatika@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "XML.h"

#include "Log.h"
#include <sstream>

namespace tinyxml2 {

// READ

bool XML::getTextBool(const XMLElement *element, bool defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get text bool, element is NULL" << std::endl;
		return defaultVal;
	}
	bool value = false;
	int ret = element->QueryBoolText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get text bool, text value is not of type "
			         << " bool in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

int XML::getTextInt(const XMLElement *element, int defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get text int, element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int ret = element->QueryIntText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get text int, text value is not of type "
			         << " int in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

unsigned int XML::getTextUInt(const XMLElement *element, unsigned int defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get text uint, element is NULL" << std::endl;
		return defaultVal;
	}
	unsigned int value = 0;
	int ret = element->QueryUnsignedText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get text uint, text value is not of type "
			         << " uint in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

float XML::getTextFloat(const XMLElement *element, float defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get text float, element is NULL" << std::endl;
		return defaultVal;
	}
	float value = 0;
	int ret = element->QueryFloatText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get text float, text value is not of type "
			         << " double in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

double XML::getTextDouble(const XMLElement *element, double defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get text double, element is NULL" << std::endl;
		return defaultVal;
	}
	double value = 0;
	int ret = element->QueryDoubleText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get text double, text value is not of type "
			         << " double in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

std::string XML::getTextString(const XMLElement *element, std::string defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get text string, element is are NULL" << std::endl;
		return defaultVal;
	}
	// try to grab value, will be NULL if empty
	const char *text = element->GetText();
	if(text == NULL) {
		return defaultVal;
	}
	return (std::string) text;
}

bool XML::getText(const XMLElement *element, XMLType type, void *var) {
	if(element == NULL || var == NULL) {
		LOG_WARN << "XML: cannot get text, element and/or variable are NULL" << std::endl;
		return false;
	}
	int ret = XML_SUCCESS;
	switch(type) {
		case XML_TYPE_BOOL: {
			bool *pVar = (bool*) var;
			(*pVar) = getTextBool(element);
			break;
		}
		
		case XML_TYPE_INT: {
			int *pVar = (int*) var;
			(*pVar) = getTextInt(element);
			break;
		}
		
		case XML_TYPE_UINT: {
			unsigned int *pVar = (unsigned int*) var;
			(*pVar) = getTextUInt(element);
			break;
		}

		case XML_TYPE_FLOAT: {
			float *pVar = (float*) var;
			(*pVar) = getTextFloat(element);
			break;
		}

		case XML_TYPE_DOUBLE: {
			double *pVar = (double*) var;
			(*pVar) = getTextDouble(element);
			break;
		}

		case XML_TYPE_STRING: {
			std::string *pVar = (std::string*) var;
			pVar->clear();
			pVar->append(getTextString(element));
			break;
		}
		
		default:
			break;
	}
	return ret;
}

bool XML::getAttrBool(const XMLElement *element, std::string name, bool defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get attribute bool, element is NULL" << std::endl;
		return defaultVal;
	}
	bool value = false;
	int ret = element->QueryBoolAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get attribute bool, attribute \"" << name
			         << "\" is not of type bool in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return (bool) value;
	}
}

int XML::getAttrInt(const XMLElement *element, std::string name, int defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get attr int, element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int ret  = element->QueryIntAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get attribute int, attribute \"" << name
			         << "\" is not of type int in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

unsigned int XML::getAttrUInt(const XMLElement *element, std::string name, unsigned int defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get attribute uint, element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int ret  = element->QueryIntAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get attribute uint, attribute \"" << name
			         << "\" is not of type int in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return (unsigned int) value;
	}
}

float XML::getAttrFloat(const XMLElement *element, std::string name, float defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get attribute float, element is NULL" << std::endl;
		return defaultVal;
	}
	float value = 0;
	int ret = element->QueryFloatAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get attribute float, attribute \"" << name
			         << "\" is not of type float in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

double XML::getAttrDouble(const XMLElement *element, std::string name, double defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get attribute double, element is NULL" << std::endl;
		return defaultVal;
	}
	double value = 0;
	int ret = element->QueryDoubleAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML: cannot get attribute double: attribute \"" << name
			         << "\" is not of type double in element \"" << element->Name()
			         << "\"" << std::endl;
			return defaultVal;
		case XML_NO_ATTRIBUTE:
			return defaultVal;
		default: // XML_SUCCESS
			return value;
	}
}

std::string XML::getAttrString(const XMLElement *element, std::string name, std::string defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get attribute string, element is are NULL" << std::endl;
		return defaultVal;
	}
	// try to grab value, will be NULL if attr does not exist
	const char *value = element->Attribute(name.c_str());
	if(value == NULL) {
		return defaultVal;
	}
	return std::string(value);
}

bool XML::getAttr(const XMLElement *element, std::string name, XMLType type, void *var) {
	if(element == NULL || var == NULL) {
		LOG_WARN << "XML: cannot get attribute, element and/or variable are NULL" << std::endl;
		return false;
	}
	int ret = XML_SUCCESS;
	switch(type) {
		case XML_TYPE_BOOL: {
			bool *pVar = (bool*) var;
			(*pVar) = getAttrBool(element, name);
			break;
		}
		
		case XML_TYPE_INT: {
			int *pVar = (int*) var;
			(*pVar) = getAttrInt(element, name);
			break;
		}
		
		case XML_TYPE_UINT: {
			unsigned int *pVar = (unsigned int*) var;
			(*pVar) = getAttrUInt(element, name);
			break;
		}

		case XML_TYPE_FLOAT: {
			float *pVar = (float*) var;
			(*pVar) = getAttrFloat(element, name);
			break;
		}

		case XML_TYPE_DOUBLE: {
			double *pVar = (double*) var;
			(*pVar) = getAttrDouble(element, name);
			break;
		}

		case XML_TYPE_STRING: {
			std::string *pVar = (std::string*) var;
			pVar->clear();
			pVar->append(getAttrString(element, name));
			break;
		}
		
		default:
			break;
	}
	return ret;
}

std::string XML::elementToString(const XMLElement *element, std::string indent) {
	if(element == NULL) {
		return "";
	}
	const XMLAttribute *xmlAttr = element->FirstAttribute();
	std::stringstream stream;
	stream << "Elem: " << element->Name() << std::endl;
	while(xmlAttr != NULL) { // loop through attributes
		stream << indent << "Attr: " << xmlAttr->Name() << " " << xmlAttr->Value();
		xmlAttr = xmlAttr->Next();
	}
	return stream.str();
}

XMLElement* XML::getChild(XMLElement *element, std::string path, int index) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get child, element is NULL" << std::endl;
		return NULL;
	}
	XMLElement *e = element;
	std::vector<PathNode> nodes = parsePath(path);
	for(unsigned int n = 0; n < nodes.size(); ++n) {
		PathNode &node = nodes[n];
		e = e->FirstChildElement(node.name.c_str());
		if(e == NULL) {
			return NULL;
		}
		for(int i = 0; i < node.index; ++i) {
			e = e->NextSiblingElement(node.name.c_str());
			if(e == NULL) {
				return NULL;
			}
		}
	}
	return e;
}

unsigned int XML::getNumChildren(XMLElement *element, std::string path, std::string name) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot get num children, element is NULL" << std::endl;
		return 0;
	}
	unsigned int num = 0;
	XMLElement *child = getChild(element, path);
	XMLElement *e = child->FirstChildElement();
	if(name == "") { // total num
		while(e != NULL) {
			num++;
			e = e->NextSiblingElement();
		}
	}
	else { // only those with a given name
		while(e != NULL) {
			num++;
			e = e->NextSiblingElement(path.c_str());
		}
	}
	return num;
}

// WRITE

void XML::setTextBool(XMLElement *element, bool b) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set text bool, element is NULL" << std::endl;
		return;
	}
	element->SetText(b ? "true" : "false");
}

void XML::setTextInt(XMLElement *element, int i) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set text int, element is NULL" << std::endl;
		return;
	}
	element->SetText(i);
}

void XML::setTextUInt(XMLElement *element, unsigned int i) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set text uint, element is NULL" << std::endl;
		return;
	}
	element->SetText(i);
}

void XML::setTextFloat(XMLElement *element, float f) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set text float, element is NULL" << std::endl;
		return;
	}
	element->SetText(f);
}

void XML::setTextDouble(XMLElement *element, double d) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set text double, element is NULL" << std::endl;
		return;
	}
	element->SetText(d);
}

void XML::setTextString(XMLElement *element, std::string s) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set text string, element is NULL" << std::endl;
		return;
	}
	element->SetText(s.c_str());
}

void XML::setText(XMLElement *element, XMLType type, void *var) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set text, element is NULL" << std::endl;
		return;
	}
	
	switch(type) {
		case XML_TYPE_BOOL: {
			bool *b = (bool*) var;
			setTextBool(element, *b);
			break;
		}

		case XML_TYPE_INT: {
			int *i = (int*) var;
			setTextInt(element, *i);
			break;
		}

		case XML_TYPE_UINT: {
			unsigned int *ui = (unsigned int*) var;
			setTextUInt(element, *ui);
			break;
		}

		case XML_TYPE_FLOAT: {
			float *f = (float*) var;
			setTextFloat(element, *f);
			break;
		}

		case XML_TYPE_DOUBLE: {
			double *d = (double*) var;
			setTextDouble(element, *d);
			break;
		}

		case XML_TYPE_STRING: {
			std::string *s = (std::string*) var;
			setTextString(element, *s);
			break;
		}

		default:
			break;
	}
}

void XML::setAttrBool(XMLElement *element, std::string name, bool b) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set attribute bool, element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), (b ? "true" : "false"));
}

void XML::setAttrInt(XMLElement *element, std::string name, int i) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set attribute int, element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), i);
}

void XML::setAttrUInt(XMLElement *element, std::string name, unsigned int i) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set attribute uint, element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), (int) i);
}

void XML::setAttrFloat(XMLElement *element, std::string name, float f) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set attribute float, element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), f);
}

void XML::setAttrDouble(XMLElement *element, std::string name, double d) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set attribute double, element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), d);
}

void XML::setAttrString(XMLElement *element, std::string name, std::string s) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot set attribute string(), element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), s.c_str());
}

void XML::setAttr(XMLElement *element, std::string name, XMLType type, void *var) {
	if(element == NULL || var == NULL) {
		LOG_WARN << "XML: cannot set attribute, element and/or variable are NULL" << std::endl;
		return;
	}
	switch(type) {
		case XML_TYPE_BOOL: {
			bool *b = (bool*) var;
			setAttrBool(element, name, *b);
			break;
		}

		case XML_TYPE_INT: {
			int *i = (int*) var;
			setAttrInt(element, name, *i);
			break;
		}

		case XML_TYPE_UINT: {
			unsigned int *ui = (unsigned int*) var;
			setAttrUInt(element, name, *ui);
			break;
		}

		case XML_TYPE_FLOAT: {
			float *f = (float*) var;
			setAttrFloat(element, name, *f);
			break;
		}

		case XML_TYPE_DOUBLE: {
			double *d = (double*) var;
			setAttrDouble(element, name, *d);
			break;
		}

		case XML_TYPE_STRING: {
			std::string *s = (std::string*) var;
			setAttrString(element, name, *s);
			break;
		}

		default:
			break;
	}
}

XMLElement* XML::addChild(XMLElement *element, std::string path, int index) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot add child, element is NULL" << std::endl;
		return NULL;
	}
	XMLElement *child = element;
	std::vector<PathNode> nodes = parsePath(path);
	for(unsigned int n = 0; n < nodes.size(); ++n) {
		PathNode &node = nodes[n];
		if(n < nodes.size()-1) { // preceeding nodes
			child = XML::obtainChild(child, node.name, node.index);
		}
		else { // last node
			XMLElement *e = element->GetDocument()->NewElement(node.name.c_str());
			XMLElement *sibling = obtainChild(child, node.name, (index > node.index ? index-1 : node.index-1));
			if(sibling) { // last node exists/was created, so insert before
				child->InsertAfterChild(sibling, e);
			}
			else {
				child->InsertEndChild(e);
			}
			child = e;
		}
	}
	return child;
}

XMLElement* XML::obtainChild(XMLElement *element, std::string path, int index) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot obtain child, element is NULL" << std::endl;
		return NULL;
	}
	XMLElement *child = element;
	std::vector<PathNode> nodes = parsePath(path);
	for(unsigned int n = 0; n < nodes.size(); ++n) {
		PathNode &node = nodes[n];
		XMLElement *e = child->FirstChildElement(node.name.c_str());
		if(e == NULL) {
			e = element->GetDocument()->NewElement(node.name.c_str());
			child->InsertEndChild(e);
		}
		int num = node.index;
		if(n == nodes.size()-1) {
			num = (index > node.index) ? index : node.index;
		}
		for(int i = 0; i < num; ++i) {
			e = e->NextSiblingElement(node.name.c_str());
			if(e == NULL) {
				e = element->GetDocument()->NewElement(node.name.c_str());
				child->InsertEndChild(e);
			}
		}
		child = e;
	}
	return child;
}

void XML::addComment(XMLElement *element, std::string comment) {
	if(element == NULL) {
		LOG_WARN << "XML: cannot add comment, element is NULL" << std::endl;
		return;
	}
	XMLComment *child = element->GetDocument()->NewComment(comment.c_str());
	element->InsertEndChild(child);
}

// UTIL

std::string XML::getErrorString(const XMLDocument *xmlDoc) {
	if(xmlDoc == NULL) {
		return "";
	}
	std::stringstream error;
	if(xmlDoc->Error()) {
		error << xmlDoc->ErrorName();
	}
	if(xmlDoc->ErrorStr()) {
		error << " " << xmlDoc->ErrorStr();
	}
	return error.str();
}

// numeric check via stringstream:
// http://stackoverflow.com/questions/4917265/can-i-tell-if-a-stdstring-represents-a-number-using-stringstream
std::vector<XML::PathNode> XML::parsePath(std::string path) {
	std::vector<XML::PathNode> nodes;
	XML::PathNode node;
	std::istringstream line(path);
	std::string token;
	while(std::getline(line, token, '/')) {
		std::stringstream numeric(token);
		int index = 0;
		if(numeric >> index) { // numeric index
			if(node.name == "") {
				LOG_ERROR << "XML: cannot parse path, found index " << token
				          << " before element name in path: " << path << std::endl;
				return std::vector<XML::PathNode>(); // empty
			}
			node.index = index;
			nodes.push_back(node);
			node.clear();
		}
		else { // element name
			if(node.name != "") { // push previous
				nodes.push_back(node);
				node.clear();
			}
			node.name = token;
		}
	}
	if(node.name != "") { // push anything left over
		nodes.push_back(node);
	}
	return nodes;
}

} // namespace
