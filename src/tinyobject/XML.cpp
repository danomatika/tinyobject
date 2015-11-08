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
		LOG_WARN << "XML::getTextBool(): element is NULL" << std::endl;
		return defaultVal;
	}
	bool value = false;
	int ret = element->QueryBoolText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getTextBool(): text value is not of type "
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
		LOG_WARN << "XML::getTextInt(): element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int ret = element->QueryIntText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getTextInt(): text value is not of type "
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
		LOG_WARN << "XML::getTextUInt(): element is NULL" << std::endl;
		return defaultVal;
	}
	unsigned int value = 0;
	int ret = element->QueryUnsignedText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getTextUInt(): text value is not of type "
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
		LOG_WARN << "XML::getTextFloat(): element is NULL" << std::endl;
		return defaultVal;
	}
	float value = 0;
	int ret = element->QueryFloatText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getTextFloat(): text value is not of type "
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
		LOG_WARN << "XML::getTextDouble(): element is NULL" << std::endl;
		return defaultVal;
	}
	double value = 0;
	int ret = element->QueryDoubleText(&value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getTextDouble(): text value is not of type "
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
		LOG_WARN << "XML::getTextString(): element is are NULL" << std::endl;
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
		LOG_WARN << "XML::getText(): element and/or variable are NULL" << std::endl;
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
		LOG_WARN << "XML::getAttrBool(): element is NULL" << std::endl;
		return defaultVal;
	}
	bool value = false;
	int ret = element->QueryBoolAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrBool(): attribute \"" << name
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
		LOG_WARN << "XML::getAttrInt(): element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int ret  = element->QueryIntAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrInt(): attribute \"" << name
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
		LOG_WARN << "XML::getAttrUInt(): element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int ret  = element->QueryIntAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrUInt(): attribute \"" << name
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
		LOG_WARN << "XML::getAttrFloat(): element is NULL" << std::endl;
		return defaultVal;
	}
	float value = 0;
	int ret = element->QueryFloatAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrFloat(): attribute \"" << name
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
		LOG_WARN << "XML::getAttrDouble(): element is NULL" << std::endl;
		return defaultVal;
	}
	double value = 0;
	int ret = element->QueryDoubleAttribute(name.c_str(), &value);
	switch(ret) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrDouble(): attribute \"" << name
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
		LOG_WARN << "XML::getAttrString(): element is are NULL" << std::endl;
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
		LOG_WARN << "XML::getAttr(): element and/or variable are NULL" << std::endl;
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

XMLElement* XML::getChild(XMLElement *element, std::string name, int index) {
	if(element == NULL) {
		LOG_WARN << "XML::getChild(): element is NULL" << std::endl;
		return NULL;
	}
	XMLElement *e = element->FirstChildElement(name.c_str());
	for(int i = 0; i < index; ++i) {
		e = element->NextSiblingElement(name.c_str());
		if(e == NULL) {
			return NULL;
		}
	}
	return e;
}

unsigned int XML::getNumChildren(XMLElement *element, std::string name) {
	if(element == NULL) {
		LOG_WARN << "XML::getNumChildren(): element is NULL" << std::endl;
		return 0;
	}
	unsigned int num = 0;
	if(name == "") { // total num
		XMLElement *e = element->FirstChildElement();
		while(e != NULL) {
			num++;
			e = e->NextSiblingElement();
		}
	}
	else { // only those with a given name
		XMLElement *e = element->FirstChildElement(name.c_str());
		while(e != NULL) {
			num++;
			e = e->NextSiblingElement(name.c_str());
		}
	}
	return num;
}

// WRITE

void XML::setTextBool(XMLElement *element, bool b) {
	if(element == NULL) {
		LOG_WARN << "XML::setTextBool(): element is NULL" << std::endl;
		return;
	}
	element->SetText(b ? "true" : "false");
}

void XML::setTextInt(XMLElement *element, int i) {
	if(element == NULL) {
		LOG_WARN << "XML::setTextInt(): element is NULL" << std::endl;
		return;
	}
	element->SetText(i);
}

void XML::setTextUInt(XMLElement *element, unsigned int i) {
	if(element == NULL) {
		LOG_WARN << "XML::setTextUInt(): element is NULL" << std::endl;
		return;
	}
	element->SetText(i);
}

void XML::setTextFloat(XMLElement *element, float f) {
	if(element == NULL) {
		LOG_WARN << "XML::setTextFloat(): element is NULL" << std::endl;
		return;
	}
	element->SetText(f);
}

void XML::setTextDouble(XMLElement *element, double d) {
	if(element == NULL) {
		LOG_WARN << "XML::setTextDouble(): element is NULL" << std::endl;
		return;
	}
	element->SetText(d);
}

void XML::setTextString(XMLElement *element, std::string s) {
	if(element == NULL) {
		LOG_WARN << "XML::setTextString(): element is NULL" << std::endl;
		return;
	}
	element->SetText(s.c_str());
}

void XML::setText(XMLElement *element, XMLType type, void *var) {
	if(element == NULL) {
		LOG_WARN << "XML::setText(): element is NULL" << std::endl;
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

void XML::setAttrString(XMLElement *element, std::string name, std::string s) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrString(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), s.c_str());
}

void XML::setAttrInt(XMLElement *element, std::string name, int i) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrInt(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), i);
}

void XML::setAttrUInt(XMLElement *element, std::string name, unsigned int i) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrUInt(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), (int) i);
}

void XML::setAttrDouble(XMLElement *element, std::string name, double d) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrDouble(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), d);
}

void XML::setAttrFloat(XMLElement *element, std::string name, float f) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrFloat(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), f);
}

void XML::setAttrBool(XMLElement *element, std::string name, bool b) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrBool(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), (b ? "true" : "false"));
}

void XML::setAttr(XMLElement *element, std::string name, XMLType type, void *var) {
	if(element == NULL || var == NULL) {
		LOG_WARN << "XML::setAttr(): element and/or variable are NULL" << std::endl;
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

XMLElement* XML::addChild(XMLElement *element, std::string name, int index) {
	if(element == NULL) {
		LOG_WARN << "XML::addChild(): element is NULL" << std::endl;
		return NULL;
	}
	XMLElement *child = element->GetDocument()->NewElement(name.c_str());
	XMLElement *sibling = getChild(element, name, index-1);
	if(sibling) {
		element->InsertAfterChild(sibling, child);
	}
	else {
		element->InsertEndChild(child);
	}
	return child;
}

XMLElement* XML::obtainChild(XMLElement *element, std::string name, int index) {
	if(element == NULL) {
		LOG_WARN << "XML::obtainChild(): element is NULL" << std::endl;
		return NULL;
	}
	XMLElement *child = getChild(element, name, index);
	if(child == NULL) { // if element doesnt exist, add it
		child = element->GetDocument()->NewElement(name.c_str());
		element->InsertEndChild(child);
	}
	return child;
}

void XML::addComment(XMLElement *element, std::string comment) {
	if(element == NULL) {
		LOG_WARN << "XML::addComment(): element is NULL" << std::endl;
		return;
	}
	XMLComment *child = element->GetDocument()->NewComment(comment.c_str());
	if(element == NULL) {
		element->InsertEndChild(child);
	}
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
	if(xmlDoc->GetErrorStr1()) {
		error << " " << xmlDoc->GetErrorStr1();
	}
	if(xmlDoc->GetErrorStr2()) {
		error << " " << xmlDoc->GetErrorStr2();
	}
	return error.str();
}

} // namespace