/*==============================================================================

	XML.cpp
	
	xmlframework: object based xml classes for TinyXml-2
  
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

bool XML::getAttrBool(const XMLElement* element, std::string name, bool defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML::getAttrBool(): element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int iRet = element->QueryIntAttribute(name.c_str(), &value);
	switch(iRet) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrBool(): attribute \"" << name
					 << "\" is not of type int in element \"" << element->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "XML::getAttrBool(): int attribute \"" << name
//                     << "\" was not found in element \"" << element->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default: // XML_SUCCESS
			return (bool) value;
	}
}

uint8_t XML::getAttrByte(const XMLElement* element, std::string name, uint8_t defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML::getAttrChar(): element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int iRet = element->QueryIntAttribute(name.c_str(), &value);
	switch(iRet) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrBool(): attribute \"" << name
					 << "\" is not of type int in element \"" << element->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "XML::getAttrBool(): int attribute \"" << name
//                     << "\" was not found in element \"" << element->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return (uint8_t) value;
	}
}

unsigned int XML::getAttrUInt(const XMLElement* element, std::string name, unsigned int defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML::getAttrUInt(): element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int iRet  = element->QueryIntAttribute(name.c_str(), &value);
	switch(iRet) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrUInt(): attribute \"" << name
					 << "\" is not of type int in element \"" << element->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "XML::getAttrUInt(): int attribute \"" << name
//                     << "\" was not found in element \"" << element->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return (unsigned int) value;
	}
}

int XML::getAttrInt(const XMLElement* element, std::string name, int defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML::getAttrInt(): element is NULL" << std::endl;
		return defaultVal;
	}
	int value = 0;
	int iRet  = element->QueryIntAttribute(name.c_str(), &value);
	switch(iRet) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrInt(): attribute \"" << name
					 << "\" is not of type int in element \"" << element->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "XML::getAttrInt(): int attribute \"" << name
//                     << "\" was not found in element \"" << element->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return value;
	}
}

float XML::getAttrFloat(const XMLElement* element, std::string name, float defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML::getAttrFloat(): element is NULL" << std::endl;
		return defaultVal;
	}
	float value = 0;
	int iRet = element->QueryFloatAttribute(name.c_str(), &value);
	switch(iRet) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrFloat(): attribute \"" << name
					 << "\" is not of type float in element \"" << element->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "XML::getAttrFloat(): float attribute \"" << name
//                     << "\" was not found in element \"" << element->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return value;
	}
}

double XML::getAttrDouble(const XMLElement* element, std::string name, double defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML::getAttrDouble(): element is NULL" << std::endl;
		return defaultVal;
	}
	double value = 0;
	int iRet = element->QueryDoubleAttribute(name.c_str(), &value);
	switch(iRet) {
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "XML::getAttrDouble(): attribute \"" << name
					 << "\" is not of type double in element \"" << element->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "XML::getAttrDouble(): double attribute \"" << name
//                     << "\" was not found in element \"" << element->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return value;
	}
}

std::string XML::getAttrString(const XMLElement* element, std::string name, std::string defaultVal) {
	if(element == NULL) {
		LOG_WARN << "XML::getAttrString(): element is are NULL" << std::endl;
		return defaultVal;
	}
	// try to grab value, will be NULL if attr does not exist
	const char* value = element->Attribute(name.c_str());
	if(value == NULL) {
//        LOG_WARN << "XML::getAttrString(): string attribute \"" << name
//                     << "\" was not found in element \"" << element->Name()
//                     << "\"" << std::endl;
		return defaultVal;
	}
	return std::string(value);
}

bool XML::getAttr(const XMLElement* element, std::string name, XMLType type, void* var) {
	if(element == NULL || var == NULL) {
		LOG_WARN << "XML::getAttr(): element and/or variable are NULL" << std::endl;
		return false;
	}
	int ret = XML_SUCCESS;
	switch(type) {
		case XML_TYPE_BOOL: {
			bool* pVar = (bool*) var;
			(*pVar) = getAttrBool(element, name);
			break;
		}
			
		case XML_TYPE_BYTE: {
			uint8_t* pVar = (uint8_t*) var;
			(*pVar) = getAttrByte(element, name);
			break;
		}
		
		case XML_TYPE_UINT: {
			unsigned int* pVar = (unsigned int*) var;
			(*pVar) = getAttrUInt(element, name);
			break;
		}

		case XML_TYPE_INT: {
			int* pVar = (int*) var;
			(*pVar) = getAttrInt(element, name);
			break;
		}

		case XML_TYPE_FLOAT: {
			float* pVar = (float*) var;
			(*pVar) = getAttrFloat(element, name);
			break;
		}

		case XML_TYPE_DOUBLE: {
			double* pVar = (double*) var;
			(*pVar) = getAttrDouble(element, name);
			break;
		}

		case XML_TYPE_STRING: {
			std::string* pVar = (std::string*) var;
			pVar->clear();
			pVar->append(getAttrString(element, name));
			break;
		}
		
		default:
			break;
	}
	return ret;
}

std::string XML::getText(const XMLElement* element, std::string defaultVal) {
	if(element == NULL) {
		return defaultVal;
	}
	const char* text = element->GetText();
	if(text == NULL) {
		return defaultVal;
	}
	return (std::string) text;
}

std::string XML::element2String(const XMLElement* element, std::string indent) {
	if(element == NULL) {
		return "";
	}
	const XMLAttribute* xmlAttr = element->FirstAttribute();
	std::stringstream stream;
	stream << "Elem: " << element->Name() << std::endl;
	while(xmlAttr != NULL) { // loop through attributes
		stream << indent << "Attr: " << xmlAttr->Name() << " " << xmlAttr->Value();
		xmlAttr = xmlAttr->Next();
	}
	return stream.str();
}

XMLElement* XML::getElement(XMLElement* element, std::string name, int index) {
	if(element == NULL) {
		LOG_WARN << "XML::getElement(): element is NULL" << std::endl;
		return NULL;
	}
	XMLHandle h(element);
	h.FirstChildElement(name.c_str());
	for(int i = 0; i < index; ++i) {
		if(h.NextSiblingElement(name.c_str()).ToNode() == NULL) {
			return NULL;
		}
	}
	return h.ToElement();
}

// WRITE

void XML::setAttrString(XMLElement* element, std::string name, std::string s) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrString(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), s.c_str());
}

void XML::setAttrInt(XMLElement* element, std::string name, int i) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrInt(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), i);
}

void XML::setAttrUInt(XMLElement* element, std::string name, unsigned int i) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrUInt(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), (int) i);
}

void XML::setAttrDouble(XMLElement* element, std::string name, double d) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrDouble(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), d);
}

void XML::setAttrFloat(XMLElement* element, std::string name, float f) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrFloat(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), f);
}

void XML::setAttrBool(XMLElement* element, std::string name, bool b) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrBool(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), (int) b);
}

void XML::setAttrByte(XMLElement* element, std::string name, uint8_t b) {
	if(element == NULL) {
		LOG_WARN << "XML::setAttrChar(): element is NULL" << std::endl;
		return;
	}
	element->SetAttribute(name.c_str(), b);
}

void XML::setAttr(XMLElement* element, std::string name, XMLType type, void* var) {
	if(element == NULL || var == NULL) {
		LOG_WARN << "XML::setAttr(): element and/or variable are NULL" << std::endl;
		return;
	}
	switch(type) {
		case XML_TYPE_BYTE: {
			uint8_t* b = (uint8_t*) var;
			setAttrByte(element, name, *b);
			break;
		}

		case XML_TYPE_BOOL: {
			bool* b = (bool*) var;
			setAttrBool(element, name, *b);
			break;
		}

		case XML_TYPE_INT: {
			int* i = (int*) var;
			setAttrInt(element, name, *i);
			break;
		}

		case XML_TYPE_UINT: {
			unsigned int* ui = (unsigned int*) var;
			setAttrUInt(element, name, *ui);
			break;
		}

		case XML_TYPE_FLOAT: {
			float* f = (float*) var;
			setAttrFloat(element, name, *f);
			break;
		}

		case XML_TYPE_DOUBLE: {
			double* d = (double*) var;
			setAttrDouble(element, name, *d);
			break;
		}

		case XML_TYPE_STRING: {
			std::string* s = (std::string*) var;
			setAttrString(element, name, *s);
			break;
		}

		default:
			break;
	}
}

void XML::setText(XMLElement* element, std::string text) {
	if(element == NULL) {
		LOG_WARN << "XML::setText(): element is NULL" << std::endl;
		return;
	}
	XMLNode* textChild = element->LastChild();
	if(textChild && (textChild->ToText() != NULL)) {
		textChild->SetValue(text.c_str());
	}
	else {
		textChild = element->GetDocument()->NewText(text.c_str());
		element->LinkEndChild(textChild);
	}
}

XMLElement* XML::obtainElement(XMLElement* element, std::string name, int index) {
	if(element == NULL) {
		LOG_WARN << "XML::addExistingElement(): element is NULL" << std::endl;
		return NULL;
	}
	XMLHandle h(element);
	XMLElement* child = getElement(element, name, index);
	if(child == NULL) { // if element doesnt exist, add it
		child = element->GetDocument()->NewElement(name.c_str());
		element->LinkEndChild(child);
	}
	return child;
}

// UTIL

std::string XML::getErrorString(const XMLDocument* xmlDoc) {
	if(xmlDoc == NULL) {
		return "";
	}
	std::stringstream error;
	if(xmlDoc->GetErrorStr1()) {
		error << xmlDoc->GetErrorStr1();
	}
	if(xmlDoc->GetErrorStr2()) {
		error << " " << xmlDoc->GetErrorStr2();
	}
	return error.str();
}

} // namespace
