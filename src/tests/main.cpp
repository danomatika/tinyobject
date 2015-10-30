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
using namespace tinyxml2;

class TestObject : public XMLObject {

	public:

		TestObject() : XMLObject("object") {}
	
	protected:
		bool readXML(tinyxml2::XMLElement* e) {
			cout << e->Name()
				 << " \"" << XML::getAttrString(e, "name", "unknown") << "\" : "
				 << e->GetText() << endl;
			return true;
		}
};

class XMLProcessor : public XMLObject {

	public:
		
		// set the object's element name
		XMLProcessor() : XMLObject("xmltest") {}
		
	protected:
	
		// derived callback, called when loading xml data for the object
		bool readXML(tinyxml2::XMLElement* e) {
			tinyxml2::XMLElement* child = e->FirstChildElement();
			while(child != NULL) {
				if((string)child->Name() == "argtest") {
					cout << "ARGUMENT TEST" << endl;
					bool boolVal1 = XML::getAttrBool(child, "bool1", false);
					bool boolVal0 = XML::getAttrBool(child, "bool0", true);
					bool boolValT = XML::getAttrBool(child, "boolT", false);
					bool boolValF = XML::getAttrBool(child, "boolF", true);
					int intVal = XML::getAttrInt(child, "int");
					unsigned int uintVal = XML::getAttrUInt(child, "uint");
					float floatVal = XML::getAttrFloat(child, "float");
					double doubleVal = XML::getAttrDouble(child, "double");
					cout << "bool 1: " << boolVal1 << endl
					     << "bool 0: " << boolVal0 << endl
					     << "bool true:  " << boolValT << endl
						 << "bool false: " << boolValF << endl
					     << "int:    " << intVal << endl
						 << "uint:   " << uintVal << endl
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
						o.loadXML(child->FirstChildElement());
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
	
	// load xml file through XMLProcessor derived from XMLObject
	XMLProcessor processor;
	processor.loadXMLFile("../../data/test.xml");

	return 0;
}
