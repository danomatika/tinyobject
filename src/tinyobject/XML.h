/*==============================================================================

	XML.h
	
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

#include <tinyxml2.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace tinyxml2 {

/// element text or attribute value type
enum XMLType {
	XML_TYPE_UNDEF = 0,
	XML_TYPE_BOOL,
	XML_TYPE_INT,
	XML_TYPE_UINT,
	XML_TYPE_FLOAT,
	XML_TYPE_DOUBLE,
	XML_TYPE_STRING
};

/// \class XML
/// \brief convenience wrappers for reading & writing element values & attributes
class XML {

	public:

	/// \section Read

		/// element text access by type,
		/// returns value on success or defaultVal if wrong type
		static bool getTextBool(const XMLElement *element, bool defaultVal=false);
		static int getTextInt(const XMLElement *element, int defaultVal=0);
		static unsigned int getTextUInt(const XMLElement *element, unsigned int defaultVal=0);
		static float getTextFloat(const XMLElement *element, float defaultVal=0.0f);
		static double getTextDouble(const XMLElement *element, double defaultVal=0.0);
		static std::string getTextString(const XMLElement *element, std::string defaultVal="");

		/// element text access using type enum
		static bool getText(const XMLElement *element, XMLType type, void *var);
	
		/// element attribute access by type
		/// returns value on success or defaultVal if attribute not found or wrong type
		static bool getAttrBool(const XMLElement *element, std::string name, bool defaultVal=false);
		static int getAttrInt(const XMLElement *element, std::string name, int defaultVal=0);
		static unsigned int getAttrUInt(const XMLElement *element, std::string name, unsigned int defaultVal=0);
		static float getAttrFloat(const XMLElement *element, std::string name, float defaultVal=0.0f);
		static double getAttrDouble(const XMLElement *element, std::string name, double defaultVal=0.0);
		static std::string getAttrString(const XMLElement *element, std::string name, std::string defaultVal="");
		
		/// element attribute access using type enum, returns true on success
		static bool getAttr(const XMLElement *element, std::string name, XMLType type, void *var);
	
		/// return element and attributes as a string, does not descend to children
		static std::string elementToString(const XMLElement *element, std::string indent);

		/// find child element by path and index (if in a list), returns NULL if element not found
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "/sub/element/test" or "/sub/1/element/2/test"
		/// if an index is given for the final element in the path along with an index argument, the greater of
		/// the two is used
		static XMLElement* getChild(XMLElement *element, std::string path, int index=0);
	
		/// get the number of child elements with the given name,
		/// if name is empty "", returns total number of child elements
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test" or "/sub/1/element/2/test"
		static unsigned int getNumChildren(XMLElement *element, std::string path="", std::string name="");

	/// \section Write

		/// set the element text
		static void setTextBool(XMLElement *element, bool b);
		static void setTextInt(XMLElement *element, int i);
		static void setTextUInt(XMLElement *element, unsigned int i);
		static void setTextFloat(XMLElement *element, float f);
		static void setTextDouble(XMLElement *element, double d);
		static void setTextString(XMLElement *element, std::string s);

		/// set the element text using type enum
		static void setText(XMLElement *element, XMLType type, void *var);

		/// set element attributes by type
		static void setAttrBool(XMLElement *element, std::string name, bool b);
		static void setAttrInt(XMLElement *element, std::string name, int i);
		static void setAttrUInt(XMLElement *element, std::string name, unsigned int i);
		static void setAttrFloat(XMLElement *element, std::string name, float f);
		static void setAttrDouble(XMLElement *element, std::string name, double d);
		static void setAttrString(XMLElement *element, std::string name, std::string s);

		/// set attribute using XMLObject type enum
		static void setAttr(XMLElement *element, std::string name, XMLType type, void *var);
	
		/// adds a child element at a specific index in a list of same elements (0 for first),
		/// adds to end if index is invalid
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test" or "/sub/1/element/2/test"
		/// if an index is given for the final element in the path along with an index argument, the greater of
		/// the two is used
		static XMLElement* addChild(XMLElement *element, std::string path, int index=0);
	
		/// finds child element at specific index in a list of same elements (0 for first),
		/// creates and adds to end if not found
		/// path can also be a / separated string to denote multiple levels of depth below the given
		/// element aka "sub/element/test" or "/sub/1/element/2/test"
		/// if an index is given for the final element in the path along with an index argument, the greater of
		/// the two is used
		static XMLElement* obtainChild(XMLElement *element, std::string path, int index=0);

		/// adds a comment as a child of the given element
		static void addComment(XMLElement *element, std::string comment);

	/// \section Util

		/// returns the current error as a string
		static std::string getErrorString(const XMLDocument *xmlDoc);
	
		/// path node struct for parsing a given path string aka
		/// "foo/bar/baz", "foo/1/bar/2/baz/3", etc
		struct PathNode {
			
			std::string name; //< element name
			int index; //< index if in a list, 0 for first element
			
			/// constructor to set default values
			PathNode() {
				clear();
			}
			
			/// reset to default values
			void clear() {
				name = "";
				index = 0;
			}
		};
	
		/// parses a given string as sets of element names and indices
		/// separated by forward slashes /
		///
		/// ie. "foo/bar/baz" -> "foo", "bar", "baz
		///     "foo/1/bar/2/baz/3" -> "foo" 1, "bar" 2, "baz" 3
		///
		/// an index before an element name string results in an error:
		///    "1/foo/bar" -> error
		///
		/// used internally as a "poor man's XPath"
		static std::vector<PathNode> parsePath(std::string path);
};

} // namespace
