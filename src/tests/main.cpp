/*==============================================================================

	main.cpp
	
	xmltests: tests for xmlframework
  
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
#include <xmlframework/xmlframework.h>
#include <iostream>

using namespace std;
using namespace xml;

class TestObject : public XmlObject {

	public:

		TestObject() : XmlObject("object") {}
	
	protected:
		bool readXml(tinyxml2::XMLElement* e) {
			cout << e->Name()
				 << " \"" << Xml::getAttrString(e, "name", "unknown") << "\" : "
				 << e->GetText() << endl;
			return true;
		}
};

class XmlProcessor : public XmlObject {

	public:
		
		// set the object's element name
		XmlProcessor() : XmlObject("xmltest") {}
		
	protected:
	
		// derived callback, called when loading xml data for the object
		bool readXml(tinyxml2::XMLElement* e) {
			tinyxml2::XMLElement* child = e->FirstChildElement();
			while(child != NULL) {
				if((string)child->Name() == "argtest") {
					cout << "ARGUMENT TEST" << endl;
					bool boolValT = Xml::getAttrBool(child, "boolT", false);
					bool boolValF = Xml::getAttrBool(child, "boolF", true);
					uint8_t byteVal = Xml::getAttrByte(child, "byte");
					unsigned int uintVal = Xml::getAttrUInt(child, "uint");
					int intVal = Xml::getAttrInt(child, "int");
					float floatVal = Xml::getAttrFloat(child, "float");
					double doubleVal = Xml::getAttrDouble(child, "double");
					cout << "boolT:  " << boolValT << endl
						 << "boolF:  " << boolValF << endl
						 << "byte:   " << (int) byteVal << endl
						 << "uint:   " << uintVal << endl
						 << "int:    " << intVal << endl
						 << "float:  " << floatVal << endl
						 << "double: " << doubleVal << endl;
					cout << "DONE" << endl << endl;
				}
				else if((string)child->Name() == "elementtest") {
					cout << "ELEMENT TEST" << endl;
					tinyxml2::XMLElement* subchild = child->FirstChildElement();
					while(subchild != NULL) {
						cout << subchild->Name() << ": \""
							 << subchild->GetText() << "\"" << endl;
						subchild = subchild->NextSiblingElement();
					}
					cout << "DONE" << endl << endl;
				}
				else if((string)child->Name() == "objecttest") {
					cout << "OBJECT TEST" << endl;
					tinyxml2::XMLElement* subchild = child->FirstChildElement();
					while(subchild != NULL) {
						TestObject o;
						o.loadXml(child->FirstChildElement());
						subchild = subchild->NextSiblingElement();
					}
					cout << "DONE" << endl << endl;
				}
				child = child->NextSiblingElement();
			}
			return true;
		}
};

int main(int argc, char *argv[]) {
	cout << endl;
	
	// load xml file through XmlProcessor derived from XmlObject
	XmlProcessor processor;
	processor.loadXmlFile("../../data/test.xml");

	return 0;
}
