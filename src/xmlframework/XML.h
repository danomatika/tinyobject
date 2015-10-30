/*==============================================================================

	XML.h
	
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
#pragma once

#include <tinyxml2.h>
#include <stdint.h>
#include "XMLObject.h"

namespace tinyxml2 {

/// \class  XML
/// \brief  convenience wrapper for some of the TinyXml-2 functions
class XML {

	public:

		/// \section Reading Member Functions

		/// attribute access by type, returns true if value found & set, false if not
		/// does not change var if if attribute not found or wrong type
		static bool getAttrBool(const XMLElement* element, std::string name, bool defaultVal=true);
		static uint8_t getAttrByte(const XMLElement* element, std::string name, uint8_t defaultVal=0); // unsigned
		static unsigned int getAttrUInt(const XMLElement* element, std::string name, unsigned int defaultVal=0);
		static int getAttrInt(const XMLElement* element, std::string name, int defaultVal=0);
		static float getAttrFloat(const XMLElement* element, std::string name, float defaultVal=0.0f);
		static double getAttrDouble(const XMLElement* element, std::string name, double defaultVal=0.0);
		static std::string getAttrString(const XMLElement* element, std::string name, std::string defaultVal="");
		
		/// attribute access using XMLObject type enum
		static bool getAttr(const XMLElement* element, std::string name, XMLType type, void* var);

		/// return the element text as a string
		static std::string getText(const XMLElement* element, std::string defaultVal="");

		/// return element and attributes as a string, does not descend to children
		static std::string element2String(const XMLElement* element, std::string indent);

		/// find child element by name and index (if in a list), returns NULL if element not found
		static XMLElement* getElement(XMLElement* element, std::string name, int index=0);

		/// \section Writing Member Functions

		static void setAttrString(XMLElement* element, std::string name, std::string s);
		static void setAttrInt(XMLElement* element, std::string name, int i);
		static void setAttrUInt(XMLElement* element, std::string name, unsigned int i);
		static void setAttrDouble(XMLElement* element, std::string name, double d);
		static void setAttrFloat(XMLElement* element, std::string name, float f);
		static void setAttrBool(XMLElement* element, std::string name, bool b);
		static void setAttrByte(XMLElement* element, std::string name, uint8_t b);

		/// set attribute using XMLObject type enum
		static void setAttr(XMLElement* element, std::string name, XMLType type, void* var);

		/// set the element text
		static void setText(XMLElement* element, std::string text);

		/// finds child element at specific index in a list of same elements (0 for first),
		/// creates and adds to end if not found
		static XMLElement* obtainElement(XMLElement* element, std::string name, int index=0);

		/// \section Utility Member Functions

		/// returns the current error as a string
		static std::string getErrorString(const XMLDocument* xmlDoc);
};

} // namespace
