/*==============================================================================

	main.cpp
	
	totest: tests for tinyobject
  
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
#include <tinyobject/tinyobject.h>
#include <iostream>

using namespace std;
using namespace tinyxml2;

// useful references:
//   * https://shilohjames.wordpress.com/2014/04/27/tinyxml2-tutorial
//   * http://www.grinninglizard.com/tinyxml2docs/index.html

// an xml object subclass
class Object : public XMLObject {

	public:

		Object() : XMLObject("object") {}
	
	protected:
	
		// read all values within callback
		bool readXML(tinyxml2::XMLElement *e) {
			name = XML::getAttrString(e, "name");
			foo = XML::getTextString(XML::getChild(e, "foo"));
			bar = XML::getTextFloat(XML::getChild(e, "bar"));
			cout << endl;
			cout << "OBJECT: " << name << endl
			     << "    foo: " << foo << endl
				 << "    bar: " << bar << endl << endl;
			return true;
		}
	
		// write all values within callback
		bool writeXML(tinyxml2::XMLElement *e) {
			XML::setAttrString(e, "name", name);
			XML::setTextString(XML::obtainChild(e, "foo"), foo);
			XML::setTextFloat(XML::obtainChild(e, "bar"), bar);
			return true;
		}
	
		string name;
		string foo;
		float bar;
};

// an xml object subclass to be nested within the first
class SubObject : public XMLObject {

	public:

		// subscribe variable references in constructor, values will be filled
		// automatically when the XML data is loaded
		SubObject() : XMLObject("subobject") {
		
			// subscribe to load attribute data, empty element name "" to
			// load from root element name of this object: "subobject"
			subscribeXMLAttribute("name", "", XML_TYPE_STRING, &name);
			
			// subscribe to load element text data
			subscribeXMLElement("baz", XML_TYPE_FLOAT, &baz);
			subscribeXMLElement("ka", XML_TYPE_STRING, &ka);
		}
	
	protected:
	
		// print values in callback
		bool readXML(XMLElement *e) {
			cout << endl;
			cout << "SUBOBJECT: " << name << endl
			     << "    baz: " << baz << endl
				 << "    ka: " << ka << endl;
			return true;
		}
	
		string name;
		float baz;
		string ka;
};

//
class Processor : public XMLObject {

	public:
		
		// set the object's element name, in this case our root element name
		Processor() : XMLObject("xmltest") {
			
			Object *object = new Object;
			SubObject *subobject = new SubObject;
			
			// next subobject inside object
			object->addXMLObject(subobject);
			
			// nest object inside this class
			addXMLObject(object);
			
			// both objects will be called with the element of the same name
			// automatically
		}
		
	protected:
	
		// derived callback, called when loading xml data for the object
		bool readXML(XMLElement *e) {
			XMLElement *child = e->FirstChildElement();
			while(child != NULL) {
				if((string)child->Name() == "argtest") {
					cout << "ARGUMENT TEST" << endl;
					cout << "bool 1: " << XML::getAttrBool(child, "bool1", false) << endl
					     << "bool 0: " << XML::getAttrBool(child, "bool0", true) << endl
					     << "bool true:  " << XML::getAttrBool(child, "boolT", false) << endl
						 << "bool false: " << XML::getAttrBool(child, "boolF", true) << endl
					     << "int:    " << XML::getAttrInt(child, "int") << endl
						 << "uint:   " << XML::getAttrUInt(child, "uint") << endl
						 << "float:  " << XML::getAttrFloat(child, "float") << endl
						 << "double: " << XML::getAttrDouble(child, "double") << endl
						 << "string: " << XML::getAttrString(child, "string") << endl;
					cout << "DONE" << endl << endl;
				}
				else if((string)child->Name() == "elementtest") {
					cout << "ELEMENT TEST: " << XML::getNumChildren(child) << endl;
					cout << "bool 1: " << XML::getTextBool(XML::getChild(child, "bool1"), false) << endl
					     << "bool 0: " << XML::getTextBool(XML::getChild(child, "bool0"), true) << endl
					     << "bool true:  " << XML::getTextBool(XML::getChild(child, "boolT"), false) << endl
						 << "bool false: " << XML::getTextBool(XML::getChild(child, "boolF"), true) << endl
					     << "int:    " << XML::getTextInt(XML::getChild(child, "int")) << endl
						 << "uint:   " << XML::getTextUInt(XML::getChild(child,  "uint")) << endl
						 << "float:  " << XML::getTextFloat(XML::getChild(child, "float")) << endl
						 << "double: " << XML::getTextDouble(XML::getChild(child, "double")) << endl
						 << "string: " << XML::getTextString(XML::getChild(child, "string")) << endl;
					cout << "DONE" << endl << endl;
				}
				else if((string)child->Name() == "objecttest") {
					// load object class manually
					XMLElement *subchild = child->FirstChildElement();
					while(subchild != NULL) {
						Object o;
						o.loadXML(child->FirstChildElement()); // prints here when the class readXML function called
						subchild = subchild->NextSiblingElement();
					}
				}
				child = child->NextSiblingElement();
			}
			return true;
		}
};

int main(int argc, char *argv[]) {
	
	// load xml file through Processor derived from XMLObject
	Processor processor;
	processor.loadXMLFile("../../data/test.xml");
	
	// close current XML document tree, comment this to save changes along with
	// everything else (key is to use XML::obtainChild so as not to add extra
	// copies of the same elements to the tree)
	processor.closeXMLFile();
	
	// save object data automatically (everything else woudl need to
	// be done manually
	processor.saveXMLFile("./testsave.xml");

	return 0;
}
