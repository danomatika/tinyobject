/*==============================================================================

	XMLObject.h
	
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
#pragma once

#include "XML.h"
#include <vector>

namespace tinyxml2 {

/// \class XMLObject
/// \brief an xml object baseclass to split up xml processing per class
///
/// subclass and implement the readXML/writeXML functions to handle
/// elements and attributes inherent to the class, you can also next objects
/// within each other to specify a hierarchy whereby the required element at the
/// specifc level within the xml document will be supplied to readXML/writeXML
///
/// also provides automatic loading/saving of primitive types via pointers
/// without having to handle things manually in readXML/writeXML
///
class XMLObject {

	public:

		/// set the xml element name, if the element is empty the element name of the parent is used
		XMLObject(std::string elementName="");
		virtual ~XMLObject();

		/// \section Load

		/// load from an xml element, checks if the element name is correct
		bool loadXML(XMLElement *e);

		/// load from an xml file, leave empty to use previous filename
		/// if already loaded/set
		bool loadXMLFile(std::string filename="");

		/// \section Save

		/// save to an xml element, checks if the element name is correct
		bool saveXML(XMLElement *e);

		/// save to a new xml file
		bool saveXMLFile(std::string filename="");

		/// close the current file (does not save, call load to open again)
		void closeXMLFile();

		/// \section Objects

		/// attach/remove an XmlObject to this one,
		/// attached object readXML & writeXML functions are called when this
		/// object is loaded or saved
		void addXMLObject(XMLObject *object);
		void removeXMLObject(XMLObject *object);

		/// \section Elements

		/// add an element at the current level, element names are singular
		/// name can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test"
		bool subscribeXMLElement(std::string name, XMLType type, void *var, bool readOnly=false);
	
		/// remove an element at the current level, also removes attached attributes
		bool unsubscribeXMLElement(std::string name);
	
		/// remove all currently
		void unsubscribeAllXMLElements();   //< also removes subscribed attributes

		/// \section Attributes
		
		/// subscribe to automatically load an attribute, element names are singular
		/// if element does not exist, it will be created
		/// if it exists, attribute will be attached to it
		/// if element name is the same as the object name, the attribute will be added to the root tag
		/// element name can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test"
		bool subscribeXMLAttribute(std::string name, std::string elementName, XMLType type, void *var, bool readOnly=false);
	
		/// unsubscribe from automatically loading an attribute
		bool unsubscribeXMLAttribute(std::string name, std::string elementName);

		/// \section Util

		/// get/set the filename
		inline std::string& getXMLFilename() {return m_filename;}
		inline void setXMLFilename(std::string name) {m_filename = name;}

		/// get/set this objects xml element name
		inline std::string& getXMLName() {return m_elementName;}
		inline void setXMLName(std::string name) {m_elementName = name;}
	
		/// is the XML document for this object currently loaded
		/// returns true if this object is currently loaded or saving
		bool isXMLDocumentLoaded();
	
		/// get the currently loaded xml document when this object is loading/saving
		/// returns NULL if the document has not been initialized or the object has a parent
		/// object doing the loading/saving
		XMLDocument* getXMLDocument();
	
		/// get the root element of the currently loaded XML document
		/// returns NULL if the document has not been initialized or the object has a parent
		/// object doing the loading/saving
		XMLElement* getXMLRootElement();

	protected:

		/// \section
	
		/// derive these callbacks for direct access to loading/saving
		/// these are called after attached elements, then objects are processed

		/// callback to process xml children when loaded, returns true if element handled
		/// param e is the root element of this object aka <getXmlName()> ...
		virtual bool readXML(XMLElement *e) {return false;}

		/// callback to save to xml when saved, returns true if successful
		/// param e is the root element of this object aka <getXmlName()> ...
		virtual bool writeXML(XMLElement *e) {return false;}

	private:

		/// subscribed attribute to load
		struct _Attribute {
			//_Attribute() : type(XML_TYPE_UNDEF) {}
			std::string name; //< attribute name
			XMLType type; //< attribute type
			void *var; //< pointer to subscribed variable
			bool readOnly; //< should this value be written when saving?
		};
	
		/// subscribed element to load
		struct _Element {
			std::string name; //< element name
			XMLType type; //< element text type
			void *var; //< pointer to subscribed variable
			bool readOnly; //< should this value be written when saving?
			std::vector<_Attribute*> attributeList; //< subscribed attributes
		};

		/// find an element in the list by its name, returns NULL if not found
		_Element* findElement(std::string name) {
			std::vector<_Element*>::iterator iter;
			for(iter = m_elementList.begin(); iter != m_elementList.end(); ++iter) {
				if((*iter)->name == name) {
					return (*iter);
				}
			}
			return NULL;
		}

		bool m_docLoaded; //< is the doc loaded?
		std::string m_filename; //< current filename
		XMLDocument *m_xmlDoc; //< the xml document

		std::string m_elementName; //< name of the root element
		std::vector<_Element*> m_elementList; //< attached elements/attributes
		std::vector<XMLObject*> m_objectList; //< attached xml objects to process
};

} // namespace
