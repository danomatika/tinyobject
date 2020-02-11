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

		/// initialize an empty xml document with a root element matching this
		/// object's element name,
		/// only needed when setting data externally before saving if you're not
		/// subclassing and/or implementing the writeXML callback
		void initXML();

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

		/// subscribe to automatically load/save an element at a path relative
		/// to the current level
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test"
		/// returns true on success
		bool subscribeXMLElement(std::string path, XMLType type, void *var, bool readOnly=false);
	
		/// unsubscribe a subscribed element at a path relative to the current level,
		/// also removes attached attributes to this element
		/// returns true on success
		bool unsubscribeXMLElement(std::string path);
	
		/// unsubscribe all subscribed elements, also removes subscribed attributes
		void unsubscribeAllXMLElements();

	/// \section Attributes
		
		/// subscribe to automatically load/save an attribute in an element at a path
		///
		/// if element does not exist, it will be created
		/// if it exists, attribute will be attached to it
		/// if path is the same as the object name, the attribute will be added to the root tag
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test"
		/// returns true on success
		bool subscribeXMLAttribute(std::string path, std::string name, XMLType type, void *var, bool readOnly=false);
	
		/// unsubscribe a subscribed attribute in an element at a path relative to the current level
		/// returns true on success
		bool unsubscribeXMLAttribute(std::string path, std::string name);
	
		/// unsubscribe all attributes, also removes elements that were not *explicityl* subscribed
		/// to via subscribeXMLElement()
		void unsubscribeAllXMLAttributes();
	
	/// \section Data Access
	/// these member functions only work when the current element is set via loadXML/initXML
	
		/// element text access by type,
		/// returns value on success or defaultVal if wrong type
		bool getXMLTextBool(std::string path, bool defaultVal=false);
		int getXMLTextInt(std::string path, int defaultVal=0);
		unsigned int getXMLTextUInt(std::string path, unsigned int defaultVal=0);
		float getXMLTextFloat(std::string path, float defaultVal=0.0f);
		double getXMLTextDouble(std::string path, double defaultVal=0.0);
		std::string getXMLTextString(std::string path, std::string defaultVal="");
	
		/// element attribute access by type
		/// returns value on success or defaultVal if attribute not found or wrong type
		bool getXMLAttrBool(std::string path, std::string name, bool defaultVal=false);
		int getXMLAttrInt(std::string path, std::string name, int defaultVal=0);
		unsigned int getXMLAttrUInt(std::string path, std::string name, unsigned int defaultVal=0);
		float getXMLAttrFloat(std::string path, std::string name, float defaultVal=0.0f);
		double getXMLAttrDouble(std::string path, std::string name, double defaultVal=0.0);
		std::string getXMLAttrString(std::string path, std::string name, std::string defaultVal="");
	
		/// find child element by path and index (if in a list), returns NULL if element not found
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "/sub/element/test" or "/sub/1/element/2/test"
		/// if an index is given for the final element in the path along with an index argument, the greater of
		/// the two is used
		XMLElement* getXMLChild(std::string path, int index=0);
	
		/// get the number of child elements with the given name,
		/// if name is empty "", returns total number of child elements
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test" or "/sub/1/element/2/test"
		unsigned int getNumXMLChildren(std::string path, std::string name="");
	
		/// set the element text
		void setXMLTextBool(std::string path, bool b);
		void setXMLTextInt(std::string path, int i);
		void setXMLTextUInt(std::string path, unsigned int i);
		void setXMLTextFloat(std::string path, float f);
		void setXMLTextDouble(std::string path, double d);
		void setXMLTextString(std::string path, std::string s);
	
		/// set element attributes by type
		void setXMLAttrBool(std::string path, std::string name, bool b);
		void setXMLAttrInt(std::string path, std::string name, int i);
		void setXMLAttrUInt(std::string path, std::string name, unsigned int i);
		void setXMLAttrFloat(std::string path, std::string name, float f);
		void setXMLAttrDouble(std::string path, std::string name, double d);
		void setXMLAttrString(std::string path, std::string name, std::string s);
	
		/// adds a child element at a specific index in a list of same elements (0 for first),
		/// adds to end if index is invalid
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test" or "/sub/1/element/2/test"
		/// if an index is given for the final element in the path along with an index argument, the greater of
		/// the two is used
		XMLElement* addXMLChild(std::string path, int index=0);
	
		/// finds child element at specific index in a list of same elements (0 for first),
		/// creates and adds to end if not found
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test" or "/sub/1/element/2/test"
		/// if an index is given for the final element in the path along with an index argument, the greater of
		/// the two is used
		XMLElement* obtainXMLChild(std::string path, int index=0);

		/// adds a comment as a child of the given element, creates elements not found in the path
		void addXMLComment(std::string path, std::string comment);

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
	
		/// get the currently loaded xml document
		/// returns NULL if the document has not been initialized
		XMLDocument* getXMLDocument();
	
		/// get the root element of the currently loaded XML document
		/// returns NULL if the document has not been initialized
		XMLElement* getXMLRootElement();
	
		/// get the xml element for this object (aka the e argument in readXML/writeXML)
		/// returns NULL if the document has not been initialized or loaded
		XMLElement* getXMLElement();

	protected:

	/// \section Object Callbacks
	
		/// derive these callbacks for direct access to loading/saving
		/// these are called after attached elements, then objects are processed

		/// callback to process xml children when loaded, returns true if element handled
		/// param e is the root element of this object aka <getXmlName()> ...
		virtual bool readXML(XMLElement *e) {return false;}

		/// callback to save to xml when saved, returns true if successful
		/// param e is the root element of this object aka <getXmlName()> ...
		virtual bool writeXML(XMLElement *e) {return false;}

	private:

		/// subscribed attribute to load/save
		struct _Attribute {
			std::string name; ///< attribute name
			XMLType type; ///< attribute type
			void *var; ///< pointer to subscribed variable
			bool readOnly; ///< should this value be written when saving?
		};
	
		/// subscribed element to load/save
		struct _Element {
			std::string path; ///< element path (or name)
			XMLType type; ///< element text type
			void *var; ///< pointer to subscribed variable
			bool readOnly; ///< should this value be written when saving?
			std::vector<_Attribute*> attributes; ///< subscribed attributes
		};

		/// find an element in the list by its path, returns NULL if not found
		_Element* findElement(std::string path) {
			std::vector<_Element*>::iterator iter;
			for(iter = m_elements.begin(); iter != m_elements.end(); ++iter) {
				if((*iter)->path == path) {
					return (*iter);
				}
			}
			return NULL;
		}

		bool m_docLoaded; ///< is the doc loaded?
		std::string m_filename; ///< current filename
		XMLDocument *m_xmlDoc; ///< xml document, NULL when not loaded
		XMLElement *m_element; ///< element for this object, NULL when not loaded

		std::string m_elementName; ///< name of the root element
		std::vector<_Element *> m_elements; ///< attached elements/attributes
		std::vector<XMLObject *> m_objects; ///< attached xml objects to process
};

} // namespace
