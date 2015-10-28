/*==============================================================================

	Xml.h
	
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
#ifndef XML_XML_H
#define XML_XML_H

#include <tinyxml2.h>

#include <stdint.h>

#include "XmlObject.h"

namespace xml {

/**
	\class  Xml
	\brief  convenience wrapper for some of the TinyXml functions
**/
class Xml
{
	public:

		/** \name Reading Member Functions **/

		/// attribute access by type, returns true if value found & set, false if not
		/// does not change var if if attribute not found or wrong type
		static bool 		getAttrBool(const tinyxml2::XMLElement* xmlPtr, std::string name, bool defaultVal=true);
		static uint8_t 		getAttrByte(const tinyxml2::XMLElement* xmlPtr, std::string name, uint8_t defaultVal=0);	// unsigned
		static unsigned int getAttrUInt(const tinyxml2::XMLElement* xmlPtr, std::string name, unsigned int defaultVal=0);
		static int 			getAttrInt(const tinyxml2::XMLElement* xmlPtr, std::string name, int defaultVal=0);
		static float 		getAttrFloat(const tinyxml2::XMLElement* xmlPtr, std::string name, float defaultVal=0.0f);
		static double 		getAttrDouble(const tinyxml2::XMLElement* xmlPtr, std::string name, double defaultVal=0.0);
		static std::string 	getAttrString(const tinyxml2::XMLElement* xmlPtr, std::string name, std::string defaultVal="");    // converts numbers to text
		
		/// attribute access using XmlObject type enum
		static bool getAttr(const tinyxml2::XMLElement* xmlPtr, std::string name, XmlType type, void* var);

		/// return the element text as a string
		static std::string getText(const tinyxml2::XMLElement* xmlPtr, std::string defaultVal="");

		/// return element and attributes as a string, does not descend to children
		static std::string element2String(const tinyxml2::XMLElement* xmlPtr, std::string indent);

		/// find child element by name and index (if in a list), returns NULL if element not found
		static tinyxml2::XMLElement* getElement(tinyxml2::XMLElement* xmlPtr, std::string name, int index=0);

		/** \name Writing Member Functions **/

		static void setAttrString(tinyxml2::XMLElement* xmlPtr, std::string name, std::string s);
		static void setAttrInt(tinyxml2::XMLElement* xmlPtr, std::string name, int i);
		static void setAttrUInt(tinyxml2::XMLElement* xmlPtr, std::string name, unsigned int i);
		static void setAttrDouble(tinyxml2::XMLElement* xmlPtr, std::string name, double d);
		static void setAttrFloat(tinyxml2::XMLElement* xmlPtr, std::string name, float f);
		static void setAttrBool(tinyxml2::XMLElement* xmlPtr, std::string name, bool b);
		static void setAttrByte(tinyxml2::XMLElement* xmlPtr, std::string name, uint8_t b);

		/// set attribute using XmlObject type enum
		static void setAttr(tinyxml2::XMLElement* xmlPtr, std::string name, XmlType type, void* var);

		/// set the element text
		static void setText(tinyxml2::XMLElement* xmlPtr, std::string text);

		/// finds child element at specific index in a list of same elements (0 for first),
		/// creates and adds to end if not found
		static tinyxml2::XMLElement* obtainElement(tinyxml2::XMLElement* xmlPtr, std::string name, int index=0);

		/** \name Utility Member Functions **/

		/// returns the current error as a string with line and col of error
		static std::string getErrorString(const tinyxml2::XMLDocument* xmlDoc);
};

} // namespace

#endif // XML_XML_H
