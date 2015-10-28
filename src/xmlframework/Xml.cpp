/*==============================================================================

	Xml.cpp
	
	xmlframework: object based xml classes for TinyXml
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "Xml.h"

#include "Log.h"

#include <sstream>

using namespace tinyxml2;

namespace xml {

/* ***** READ ***** */

bool Xml::getAttrBool(const XMLElement* xmlPtr, std::string name, bool defaultVal)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getAttrBool(): element is NULL" << std::endl;
		return defaultVal;
	}

	int value = 0;
	int iRet = xmlPtr->QueryIntAttribute(name.c_str(), &value);

	switch(iRet)
	{
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "Xml::getAttrBool(): attribute \"" << name
					 << "\" is not of type int in element \"" << xmlPtr->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "Xml::getAttrBool(): int attribute \"" << name
//                     << "\" was not found in element \"" << xmlPtr->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return (bool) value;
	}
}

uint8_t Xml::getAttrByte(const XMLElement* xmlPtr, std::string name, uint8_t defaultVal)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getAttrChar(): element is NULL" << std::endl;
		return defaultVal;
	}

	int value = 0;
	int iRet = xmlPtr->QueryIntAttribute(name.c_str(), &value);

	switch(iRet)
	{
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "Xml::getAttrBool(): attribute \"" << name
					 << "\" is not of type int in element \"" << xmlPtr->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "Xml::getAttrBool(): int attribute \"" << name
//                     << "\" was not found in element \"" << xmlPtr->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return (uint8_t) value;
	}
}

unsigned int Xml::getAttrUInt(const XMLElement* xmlPtr, std::string name, unsigned int defaultVal)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getAttrUInt(): element is NULL" << std::endl;
		return defaultVal;
	}

	int value = 0;
	int iRet  = xmlPtr->QueryIntAttribute(name.c_str(), &value);
	switch(iRet)
	{
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "Xml::getAttrUInt(): attribute \"" << name
					 << "\" is not of type int in element \"" << xmlPtr->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "Xml::getAttrUInt(): int attribute \"" << name
//                     << "\" was not found in element \"" << xmlPtr->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return (unsigned int) value;
	}
}

int Xml::getAttrInt(const XMLElement* xmlPtr, std::string name, int defaultVal)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getAttrInt(): element is NULL" << std::endl;
		return defaultVal;
	}

	int value = 0;
	int iRet  = xmlPtr->QueryIntAttribute(name.c_str(), &value);
	switch(iRet)
	{
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "Xml::getAttrInt(): attribute \"" << name
					 << "\" is not of type int in element \"" << xmlPtr->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "Xml::getAttrInt(): int attribute \"" << name
//                     << "\" was not found in element \"" << xmlPtr->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return value;
	}
}

float Xml::getAttrFloat(const XMLElement* xmlPtr, std::string name, float defaultVal)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getAttrFloat(): element is NULL" << std::endl;
		return defaultVal;
	}

	float value = 0;
	int iRet = xmlPtr->QueryFloatAttribute(name.c_str(), &value);
	switch(iRet)
	{
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "Xml::getAttrFloat(): attribute \"" << name
					 << "\" is not of type float in element \"" << xmlPtr->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "Xml::getAttrFloat(): float attribute \"" << name
//                     << "\" was not found in element \"" << xmlPtr->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return value;
	}
}

double Xml::getAttrDouble(const XMLElement* xmlPtr, std::string name, double defaultVal)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getAttrDouble(): element is NULL" << std::endl;
		return defaultVal;
	}

	double value = 0;
	int iRet = xmlPtr->QueryDoubleAttribute(name.c_str(), &value);
	switch(iRet)
	{
		case XML_WRONG_ATTRIBUTE_TYPE:
			LOG_WARN << "Xml::getAttrDouble(): attribute \"" << name
					 << "\" is not of type double in element \"" << xmlPtr->Name()
					 << "\"" << std::endl;
			return defaultVal;

		case XML_NO_ATTRIBUTE:
//            LOG_WARN << "Xml::getAttrDouble(): double attribute \"" << name
//                     << "\" was not found in element \"" << xmlPtr->Name()
//                     << "\"" << std::endl;
			return defaultVal;

		default:    // XML_SUCCESS:
			return value;
	}
}

std::string Xml::getAttrString(const XMLElement* xmlPtr, std::string name, std::string defaultVal)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getAttrString(): element is are NULL" << std::endl;
		return defaultVal;
	}

	// try to grab value, will be NULL if attr does not exist
	const char* value = xmlPtr->Attribute(name.c_str());
	if(value == NULL)
	{
//        LOG_WARN << "Xml::getAttrString(): string attribute \"" << name
//                     << "\" was not found in element \"" << xmlPtr->Name()
//                     << "\"" << std::endl;
		return defaultVal;
	}
	
	return std::string(value);
}

bool Xml::getAttr(const XMLElement* xmlPtr, std::string name, XmlType type, void* var)
{
	if(xmlPtr == NULL || var == NULL)
	{
		LOG_ERROR << "Xml::getAttr(): element and/or variable are NULL" << std::endl;
		return false;
	}

	int ret = XML_SUCCESS;
	switch(type)
	{
		case XML_TYPE_BOOL:
		{
			bool* pVar = (bool*) var;
			(*pVar) = getAttrBool(xmlPtr, name);
			break;
		}
			
		case XML_TYPE_BYTE:
		{
			uint8_t* pVar = (uint8_t*) var;
			(*pVar) = getAttrByte(xmlPtr, name);
			break;
		}
		
		case XML_TYPE_UINT:
		{
			unsigned int* pVar = (unsigned int*) var;
			(*pVar) = getAttrUInt(xmlPtr, name);
			break;
		}

		case XML_TYPE_INT:
		{
			int* pVar = (int*) var;
			(*pVar) = getAttrInt(xmlPtr, name);
			break;
		}

		case XML_TYPE_FLOAT:
		{
			float* pVar = (float*) var;
			(*pVar) = getAttrFloat(xmlPtr, name);
			break;
		}

		case XML_TYPE_DOUBLE:
		{
			double* pVar = (double*) var;
			(*pVar) = getAttrDouble(xmlPtr, name);
			break;
		}

		case XML_TYPE_STRING:
		{
			std::string* pVar = (std::string*) var;
			pVar->clear();
			pVar->append(getAttrString(xmlPtr, name));
			break;
		}
		
		default:
			break;
	}

	return ret;
}

std::string Xml::getText(const XMLElement* xmlPtr, std::string defaultVal)
{
	if(xmlPtr == NULL)
	{
		return defaultVal;
	}

	const char* text = xmlPtr->GetText();
	if(text == NULL)
		return defaultVal;

	return (std::string) text;
}

std::string Xml::element2String(const XMLElement* xmlPtr, std::string indent)
{
	if(xmlPtr == NULL)
	{
		return "";
	}

	const XMLAttribute* xmlAttr = xmlPtr->FirstAttribute();

	std::stringstream stream;
	stream << "Elem: " << xmlPtr->Name() << std::endl;

	// loop through attributes
	while(xmlAttr != NULL)
	{
		stream << indent << "Attr: " << xmlAttr->Name() << " " << xmlAttr->Value();
		xmlAttr = xmlAttr->Next();
	}

	return stream.str();
}

XMLElement* Xml::getElement(XMLElement* xmlPtr, std::string name, int index)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::getElement(): element is NULL" << std::endl;
		return NULL;
	}

	XMLHandle h(xmlPtr);
	h.FirstChildElement(name.c_str());
	for(int i = 0; i < index; ++i) {
		if(h.NextSiblingElement(name.c_str()).ToNode() == NULL) {
			return NULL;
		}
	}
	return h.ToElement();
}

/* ***** WRITE ***** */

void Xml::setAttrString(XMLElement* xmlPtr, std::string name, std::string s)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setAttrString(): element is NULL" << std::endl;
		return;
	}

	xmlPtr->SetAttribute(name.c_str(), s.c_str());
}

void Xml::setAttrInt(XMLElement* xmlPtr, std::string name, int i)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setAttrInt(): element is NULL" << std::endl;
		return;
	}

	xmlPtr->SetAttribute(name.c_str(), i);
}

void Xml::setAttrUInt(XMLElement* xmlPtr, std::string name, unsigned int i)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setAttrUInt(): element is NULL" << std::endl;
		return;
	}

	xmlPtr->SetAttribute(name.c_str(), (int) i);
}

void Xml::setAttrDouble(XMLElement* xmlPtr, std::string name, double d)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setAttrDouble(): element is NULL" << std::endl;
		return;
	}

	xmlPtr->SetAttribute(name.c_str(), d);
}

void Xml::setAttrFloat(XMLElement* xmlPtr, std::string name, float f)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setAttrFloat(): element is NULL" << std::endl;
		return;
	}

	xmlPtr->SetAttribute(name.c_str(), f);
}

void Xml::setAttrBool(XMLElement* xmlPtr, std::string name, bool b)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setAttrBool(): element is NULL" << std::endl;
		return;
	}

	xmlPtr->SetAttribute(name.c_str(), (int) b);
}

void Xml::setAttrByte(XMLElement* xmlPtr, std::string name, uint8_t b)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setAttrChar(): element is NULL" << std::endl;
		return;
	}

	xmlPtr->SetAttribute(name.c_str(), b);
}

void Xml::setAttr(XMLElement* xmlPtr, std::string name, XmlType type, void* var)
{
	if(xmlPtr == NULL || var == NULL)
	{
		LOG_ERROR << "Xml::setAttr(): element and/or variable are NULL" << std::endl;
		return;
	}

	switch(type)
	{
		case XML_TYPE_BYTE:
		{
			uint8_t* b = (uint8_t*) var;
			setAttrByte(xmlPtr, name, *b);
			break;
		}

		case XML_TYPE_BOOL:
		{
			bool* b = (bool*) var;
			setAttrBool(xmlPtr, name, *b);
			break;
		}

		case XML_TYPE_INT:
		{
			int* i = (int*) var;
			setAttrInt(xmlPtr, name, *i);
			break;
		}

		case XML_TYPE_UINT:
		{
			unsigned int* ui = (unsigned int*) var;
			setAttrUInt(xmlPtr, name, *ui);
			break;
		}

		case XML_TYPE_FLOAT:
		{
			float* f = (float*) var;
			setAttrFloat(xmlPtr, name, *f);
			break;
		}

		case XML_TYPE_DOUBLE:
		{
			double* d = (double*) var;
			setAttrDouble(xmlPtr, name, *d);
			break;
		}

		case XML_TYPE_STRING:
		{
			std::string* s = (std::string*) var;
			setAttrString(xmlPtr, name, *s);
			break;
		}

		default:
			break;
	}
}

void Xml::setText(XMLElement* xmlPtr, std::string text)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::setText(): element is NULL" << std::endl;
		return;
	}

	XMLNode* textChild = xmlPtr->LastChild();
	if(textChild && (textChild->ToText() != NULL)) {
		textChild->SetValue(text.c_str());
	}
	else {
		textChild = xmlPtr->GetDocument()->NewText(text.c_str());
		xmlPtr->LinkEndChild(textChild);
	}
}

XMLElement* Xml::obtainElement(XMLElement* xmlPtr, std::string name, int index)
{
	if(xmlPtr == NULL)
	{
		LOG_ERROR << "Xml::addExistingElement(): element is NULL" << std::endl;
		return NULL;
	}

	XMLHandle h(xmlPtr);

	// if element doesnt exist, add it
	XMLElement* child = getElement(xmlPtr, name, index);
	if(child == NULL)
	{
		child = xmlPtr->GetDocument()->NewElement(name.c_str());
		xmlPtr->LinkEndChild(child);
	}

	return child;
}

/* ***** UTIL ***** */

std::string Xml::getErrorString(const XMLDocument* xmlDoc)
{
	if(xmlDoc == NULL)
		return "";

	std::stringstream error;
	if(xmlDoc->GetErrorStr1())
	{
		error << xmlDoc->GetErrorStr1();
	}
	if(xmlDoc->GetErrorStr2())
	{
		error << " " << xmlDoc->GetErrorStr2();
	}
	return error.str();
}

} // namespace
