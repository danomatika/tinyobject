/*==============================================================================

	XMLObject.cpp
	
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
#include "XmlObject.h"

#include <map>
#include <algorithm>
#include "Log.h"
#include "Xml.h"

//#define DEBUG_XML_OBJECT

namespace tinyxml2 {

XMLObject::XMLObject(std::string elementName) :
	m_docLoaded(false), m_xmlDoc(NULL), m_element(NULL), m_elementName(elementName) {}

XMLObject::~XMLObject() {
	unsubscribeAllXMLElements();
	closeXMLFile();
}

void XMLObject::initXML() {
	if(m_docLoaded) {
		closeXMLFile();
	}
	m_xmlDoc = new XMLDocument;

	// add the default declaration: 1.0 UTF-8
	m_xmlDoc->InsertEndChild(m_xmlDoc->NewDeclaration());

	// add root element
	XMLElement *root = m_xmlDoc->NewElement(getXMLName().c_str());
	m_xmlDoc->InsertEndChild(root);
	m_element = root;

	m_docLoaded = true;
}

// LOAD

bool XMLObject::loadXML(XMLElement *e) {
	if(e == NULL) {
		return false;
	}

	// check if the element is correct
	if(!m_elementName.empty() && (std::string)e->Name() != m_elementName) {
		LOG_WARN << "XML \"" << m_elementName << "\": wrong xml element name \""
		         << e->Name() << "\" for object with element name \""
		         << m_elementName << "\"" << std::endl;
		return false;
	}
	m_element = e;

	#ifdef DEBUG_XML_OBJECT
		LOG_DEBUG << "loading xml " << m_elementName << std::endl;
	#endif

	XMLElement *child;

	// load attached elements
	for(unsigned int i = 0; i < m_elementList.size(); ++i) {
		_Element *elem = m_elementList.at(i);

		#ifdef DEBUG_XML_OBJECT
			LOG_DEBUG << "elem: " << elem->name << std::endl;
		#endif

		// check if this element is the same as the root
		if((std::string)e->Name() == elem->name) {
			child = e;
		}
		else { // try to find a child with the same element name
			child = XML::getChild(e, elem->name);
		}

		if(child != NULL) {

			// load the elements text
			if(elem->var != NULL) {
				XML::getText(child, elem->type, elem->var);
			}

			// load the attached attributes
			for(unsigned int j = 0; j < elem->attributeList.size(); ++j) {
				_Attribute *attr = elem->attributeList.at(j);
				#ifdef DEBUG_XML_OBJECT
					LOG_DEBUG << "    attr: " << attr->name << std::endl;
				#endif
				XML::getAttr(child, attr->name, attr->type, attr->var);
			}
		}
	}

	// keep track of how many elements with the same name
	std::map<std::string, int> elementMap;

	// load attached objects
	std::vector<XMLObject*>::iterator objectIter;
	for(objectIter = m_objectList.begin(); objectIter != m_objectList.end();) {

		// remove this object if it dosent exist anymore
		if((*objectIter) == NULL) {
			objectIter = m_objectList.erase(objectIter);
			LOG_WARN << "XML \"" << m_elementName << "\" load: removed NULL xml object" << std::endl;
		}
		else { // exists
			XMLElement *elementToLoad = NULL;
		
			// check the parent element
			if((*objectIter)->getXMLName() == "" ||
				(*objectIter)->getXMLName() == (std::string)e->Name()) {
				// same element as parent
				elementToLoad = e;
			}
			else { // find element in list using xml name

				// try to find element name in map
				std::map<std::string, int>::iterator iter = elementMap.find((*objectIter)->getXMLName());
				if(iter == elementMap.end()) {
					// not found, so add element name to map
					elementMap.insert(make_pair((*objectIter)->getXMLName(), 0));
					iter = elementMap.find((*objectIter)->getXMLName());
				}
				else {
					iter->second++; // found another
				}

				// try to find an element with same name as the object by index (if multiples)
				elementToLoad = XML::getChild(e, (*objectIter)->getXMLName(), iter->second);
			}
				
			// load the element
			if(elementToLoad != NULL) {
				#ifdef DEBUG_XML_OBJECT
					LOG_DEBUG << "object: " << (*objectIter)->getXMLName()
					          << " " << e->Name() << std::endl;
				#endif
				(*objectIter)->loadXML(elementToLoad);  // found element
			}
			else {
				LOG_WARN << "XMLObject: element not found for \""
				         << (*objectIter)->getXMLName() << "\" object" << std::endl;
			}

			++objectIter; // increment iter
		}
	}

	// process user callback
	return readXML(e);
}

bool XMLObject::loadXMLFile(std::string filename) {
	// close if loaded
	if(m_docLoaded) {
		closeXMLFile();
	}

	// if not set, try using previous filename
	if(filename == "") {
		filename = m_filename;
	}

	// try to load the file
	m_xmlDoc = new XMLDocument;
	int ret = m_xmlDoc->LoadFile(filename.c_str());
	if(ret != XML_SUCCESS) {
		LOG_ERROR << "XML \"" << m_elementName << "\": could not load \"" << filename
		          << "\": " << XML::getErrorString(m_xmlDoc) << std::endl;
		closeXMLFile();
		return false;
	}

	// get the root element
	XMLElement *root = m_xmlDoc->RootElement();

	// check if the root is correct
	if(!root || (std::string)root->Name() != m_elementName) {
		LOG_ERROR << "XML \"" << m_elementName << "\": xml file \"" << filename
		          << "\" does not have \"" << m_elementName << "\" as the root element"
		          << std::endl;
		closeXMLFile();
		return false;
	}

	m_filename = filename;
	m_docLoaded = true;

	// load everything
	return loadXML(root);
}

// SAVE

bool XMLObject::saveXML(XMLElement *e) {
	if(e == NULL) {
		return false;
	}

	// check if the element is correct
	if(!m_elementName.empty() && (std::string)e->Name() != m_elementName) {
		LOG_WARN << "XML \"" << m_elementName << "\": xml element value is not \""
		         << m_elementName << "\"" << std::endl;
		return false;
	}
	m_element = e;

	#ifdef DEBUG_XML_OBJECT
		LOG_DEBUG << "saving xml " << m_elementName << std::endl;
	#endif

	XMLElement *child;

	// save attached elements
	for(unsigned int i = 0; i < m_elementList.size(); ++i) {
		_Element *elem = m_elementList.at(i);

		#ifdef DEBUG_XML_OBJECT
			LOG_DEBUG << "elem: " << elem->name << std::endl;
		#endif

		// check if this element is the same as the root
		if((std::string)e->Name() == elem->name) {
			child = e;
		}
		else {
			// find element, add if it dosen't exit
			child = XML::obtainChild(e, elem->name);
		}

		// set the element's text if any
		if(elem->var != NULL && !elem->readOnly) {
			XML::setText(child, elem->type, elem->var);
		}

		// save the element's attached attributes
		for(unsigned int j = 0; j < elem->attributeList.size(); ++j) {
			_Attribute *attr = elem->attributeList.at(j);
			#ifdef DEBUG_XML_OBJECT
				LOG_DEBUG << "    attr: " << attr->name << std::endl;
			#endif
			if(!attr->readOnly) {
				XML::setAttr(child, attr->name, attr->type, attr->var);
			}
		}
	}

	// keep track of how many elements with the same name
	std::map<std::string, int> elementMap;

	// save all attached objects
	bool ret = true;
	std::vector<XMLObject*>::iterator objectIter;
	for(objectIter = m_objectList.begin(); objectIter != m_objectList.end();) {
		
		// remove this object if it dosent exist anymore
		if((*objectIter) == NULL) {
			m_objectList.erase(objectIter);
			LOG_WARN << "XML \"" << m_elementName << "\" save: removed NULL xml object" << std::endl;
			++objectIter; // increment iter
		}
		else { // exists

			// if the object has an element name, find that element
			if(!(*objectIter)->getXMLName().empty()) {

				// try to find element name in map
				std::map<std::string, int>::iterator iter = elementMap.find((*objectIter)->getXMLName());
				if(iter == elementMap.end()) {
					// not found, so add element name to map
					elementMap.insert(make_pair((*objectIter)->getXMLName(), 0));
					iter = elementMap.find((*objectIter)->getXMLName());
				}
				else {
					iter->second++; // found another
				}

				#ifdef DEBUG_XML_OBJECT
					LOG_DEBUG << "object: " << (*objectIter)->getXMLName() << " " << iter->second << std::endl;
				#endif

				// find an element with same name at a specific index, add if it dosen't exist
				child = XML::obtainChild(e, (*objectIter)->getXMLName(), iter->second);
			}
			else {
				// stay on same element
				child = e;
			}

			// save object
			(*objectIter)->saveXML(child);
			++objectIter; // increment iter
		}
	}

	// process user callback
	return writeXML(e) || ret;
}

bool XMLObject::saveXMLFile(std::string filename) {
	XMLElement *root;

	// setup new doc if not loaded
	if(!m_docLoaded) {
		initXML();
	}
	root = m_xmlDoc->RootElement();

	// use the current filename?
	if(filename == "") {
		filename = m_filename;
	}

	// load data into the elements
	bool ret = saveXML(root);

	// try saving
	if(m_xmlDoc->SaveFile(filename.c_str()) != XML_SUCCESS) {
		LOG_ERROR << "XML \"" << m_elementName << "\": could not save to \""
		          << filename << "\"" << std::endl;
		return false;
	}
	return ret;
}

void XMLObject::closeXMLFile() {
	if(m_docLoaded) {
		delete m_xmlDoc;
		m_xmlDoc = NULL;
		m_element = NULL;
	}
	m_docLoaded = false;
}

// OBJECTS

void XMLObject::addXMLObject(XMLObject *object) {
	if(object == NULL) {
		LOG_WARN << "XML: Cannot add NULL object" << std::endl;
		return;
	}
	m_objectList.push_back(object);
}

void XMLObject::removeXMLObject(XMLObject *object) {
	if(object == NULL) {
		LOG_WARN << "XML: Cannot remove NULL object" << std::endl;
		return;
	}
	std::vector<XMLObject*>::iterator iter;
	iter = find(m_objectList.begin(), m_objectList.end(), object);
	if(iter != m_objectList.end()) {
		m_objectList.erase(iter);
	}
}

// ELEMENTS

bool XMLObject::subscribeXMLElement(std::string name, XMLType type, void *var, bool readOnly) {
	if(name == "") {
		name = m_elementName;
	}

	// bail if element already exists
	_Element *element;
	if((element = findElement(name)) != NULL) {
		LOG_WARN << "XML \"" << m_elementName << "\": cannot add element \"" << name
		         << "\", element already exists" << std::endl;
		return false;
	}

	// add
	element = new _Element;
	element->name = name;
	element->type = type;
	element->var = var;
	element->readOnly = readOnly;
	m_elementList.push_back(element);

	return true;
}

bool XMLObject::unsubscribeXMLElement(std::string name) {
	std::vector<_Element*>::iterator iter;
	for(iter = m_elementList.begin(); iter != m_elementList.end(); ++iter) {
		if((*iter)->name == name) {
			delete (*iter);
			m_elementList.erase(iter);
			return true;
		}
	}
	LOG_WARN << "XML \"" << m_elementName << "\": cannot remove element \""
	         << name << "\", not found" << std::endl;
	return false;
}

void XMLObject::unsubscribeAllXMLElements() {
	for(unsigned int i = 0; i < m_elementList.size(); ++i) {
		_Element *e = m_elementList.at(i);
		for(unsigned int j = 0; j < e->attributeList.size(); ++j) {
			_Attribute *attr = e->attributeList.at(j);
			delete attr;
		}
		delete e;
	}
	m_elementList.clear();
}

// ATTRIBUTES

bool XMLObject::subscribeXMLAttribute(std::string name, std::string elementName, XMLType type, void *var, bool readOnly) {
	if(name == "") {// || elementName == "") {
		LOG_WARN << "XML \"" << m_elementName << "\": cannot add attribute \"" << name
		          << "\" to element \"" << elementName << "\", name and/or element name are empty"
		          << std::endl;
		return false;
	}
	if(var == NULL) {
		LOG_WARN << "XML \"" << m_elementName << "\": attribute \"" << name
		         << "\" variable is NULL" << std::endl;
		return false;
	}
	
	// if empty, use object element name itself
	if(elementName == "") {
		elementName = m_elementName;
	}

	// check if the requested element exists, if not add it
	_Element *e = findElement(elementName);
	if(e == NULL) {
		subscribeXMLElement(elementName, XML_TYPE_UNDEF, NULL, readOnly);
		e = m_elementList.back();
	}

	_Attribute *attribute = new _Attribute;
	attribute->name = name;
	attribute->type = type;
	attribute->var = var;
	attribute->readOnly = readOnly;

	e->attributeList.push_back(attribute);

	return true;
}

bool XMLObject::unsubscribeXMLAttribute(std::string name, std::string elementName) {
	_Element *e = findElement(elementName);
	if(e == NULL) {
		return false;
	}
	std::vector<_Attribute*>::iterator iter;
	for(iter = e->attributeList.begin(); iter != e->attributeList.end(); ++iter) {
		delete (*iter);
		e->attributeList.erase(iter);
		return true;
	}
	LOG_WARN << "XML \"" << m_elementName << "\": cannot remove attribute \""
	         << name << "\", not found" << std::endl;
	return false;
}

// DATA ACCESS

bool XMLObject::getXMLTextBool(std::string path, bool defaultVal) {
	return XML::getTextBool(XML::getChild(m_element, path), defaultVal);
}

int XMLObject::getXMLTextInt(std::string path, int defaultVal) {
	return XML::getTextInt(XML::getChild(m_element, path), defaultVal);
}

unsigned int XMLObject::getXMLTextUInt(std::string path, unsigned int defaultVal) {
	return XML::getTextUInt(XML::getChild(m_element, path), defaultVal);
}

float XMLObject::getXMLTextFloat(std::string path, float defaultVal) {
	return XML::getTextFloat(XML::getChild(m_element, path), defaultVal);
}

double XMLObject::getXMLTextDouble(std::string path, double defaultVal) {
	return XML::getTextDouble(XML::getChild(m_element, path), defaultVal);
}

std::string XMLObject::getXMLTextString(std::string path, std::string defaultVal) {
	return XML::getTextString(XML::getChild(m_element, path), defaultVal);
}

bool XMLObject::getXMLAttrBool(std::string path, std::string name, bool defaultVal){
	return XML::getAttrBool(XML::getChild(m_element, path), name, defaultVal);
}

int XMLObject::getXMLAttrInt(std::string path, std::string name, int defaultVal) {
	return XML::getAttrInt(XML::getChild(m_element, path), name, defaultVal);
}

unsigned int XMLObject::getXMLAttrUInt(std::string path, std::string name, unsigned int defaultVal) {
	return XML::getAttrUInt(XML::getChild(m_element, path), name, defaultVal);
}

float XMLObject::getXMLAttrFloat(std::string path, std::string name, float defaultVal) {
	return XML::getAttrFloat(XML::getChild(m_element, path), name, defaultVal);
}

double XMLObject::getXMLAttrDouble(std::string path, std::string name, double defaultVal) {
	return XML::getAttrDouble(XML::getChild(m_element, path), name, defaultVal);
}

std::string XMLObject::getXMLAttrString(std::string path, std::string name, std::string defaultVal) {
	return XML::getAttrString(XML::getChild(m_element, path), name, defaultVal);
}

XMLElement* XMLObject::getXMLChild(std::string path, int index) {
	return XML::getChild(m_element, path, index);
}

unsigned int XMLObject::getNumXMLChildren(std::string path, std::string name) {
	return XML::getNumChildren(XML::getChild(m_element, path), name);
}

void XMLObject::setXMLTextBool(std::string path, bool b) {
	XML::setTextBool(XML::obtainChild(m_element, path), b);
}

void XMLObject::setXMLTextInt(std::string path, int i) {
	XML::setTextInt(XML::obtainChild(m_element, path), i);
}

void XMLObject::setXMLTextUInt(std::string path, unsigned int i) {
	XML::setTextUInt(XML::obtainChild(m_element, path), i);
}

void XMLObject::setXMLTextFloat(std::string path, float f) {
	XML::setTextFloat(XML::obtainChild(m_element, path), f);
}

void XMLObject::setXMLTextDouble(std::string path, double d) {
	XML::setTextDouble(XML::obtainChild(m_element, path), d);
}

void XMLObject::setXMLTextString(std::string path, std::string s) {
	XML::setTextString(XML::obtainChild(m_element, path), s);
}

void XMLObject::setXMLAttrBool(std::string path, std::string name, bool b) {
	XML::setAttrBool(XML::obtainChild(m_element, path), name, b);
}

void XMLObject::setXMLAttrInt(std::string path, std::string name, int i) {
	XML::setAttrInt(XML::obtainChild(m_element, path), name, i);
}

void XMLObject::setXMLAttrUInt(std::string path, std::string name, unsigned int i) {
	XML::setAttrUInt(XML::obtainChild(m_element, path), name, i);
}

void XMLObject::setXMLAttrFloat(std::string path, std::string name, float f) {
	XML::setAttrFloat(XML::obtainChild(m_element, path), name, f);
}

void XMLObject::setXMLAttrDouble(std::string path, std::string name, double d) {
	XML::setAttrDouble(XML::obtainChild(m_element, path), name, d);
}

void XMLObject::setXMLAttrString(std::string path, std::string name, std::string s) {
	XML::setAttrString(XML::obtainChild(m_element, path), name, s);
}

XMLElement* XMLObject::addXMLChild(std::string path, int index) {
	return XML::addChild(m_element, path, index);
}

XMLElement* XMLObject::obtainXMLChild(std::string path, int index) {
	return XML::obtainChild(m_element, path, index);
}

void XMLObject::addXMLComment(std::string path, std::string comment) {
	XML::addComment(XML::obtainChild(m_element, path), comment);
}

// UTIL

bool XMLObject::isXMLDocumentLoaded() {
	return m_docLoaded;
}

XMLDocument* XMLObject::getXMLDocument() {
	return m_xmlDoc;
}

XMLElement* XMLObject::getXMLRootElement() {
	if(m_docLoaded) {
		return m_xmlDoc->RootElement();
	}
	else {
		return NULL;
	}
}

} // namespace
