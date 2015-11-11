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
			name = getXMLAttrString("", "name");
			foo = getXMLTextString("foo");
			bar = getXMLTextFloat("bar");
			text = getXMLTextString("subelement/test/text");
			number = getXMLTextFloat("subelement/test/number");
			cout << "OBJECT: " << name << endl
			     << "    foo: " << foo << endl
			     << "    bar: " << bar << endl
				 << "    num test subelements: " << getNumXMLChildren("subelement/test") << endl
			     << "    subelement/test/text: " << text << endl
			     << "    subelement/test/number: " << number << endl;
			return true;
		}
	
		// write all values within callback
		bool writeXML(tinyxml2::XMLElement *e) {
			setXMLAttrString("", "name", name);
			setXMLTextString("foo", foo);
			setXMLTextFloat("bar", bar);
			return true;
		}
	
		string name;
		string foo;
		float bar;
	
		string text;
		float number;
};

// an xml object subclass to be nested within the first
class SubObject : public XMLObject {

	public:

		// subscribe variable references in constructor, values will be filled
		// automatically when the XML data is loaded
		SubObject() : XMLObject("subobject") {
		
			// subscribe to load attribute data, empty element name "" to
			// load from root element name of this object: "subobject"
			subscribeXMLAttribute("", "name", XML_TYPE_STRING, &name);
			
			// subscribe to load element text data
			subscribeXMLElement("baz", XML_TYPE_FLOAT, &baz);
			subscribeXMLElement("ka", XML_TYPE_STRING, &ka);
			
			// subscribe to nested elements
			subscribeXMLElement("subelement/test/text", XML_TYPE_STRING, &text);
			subscribeXMLElement("subelement/test/number", XML_TYPE_FLOAT, &number);
		}
	
	protected:
	
		// print values in callback
		bool readXML(XMLElement *e) {
			cout << "SUBOBJECT: " << name << endl
			     << "    baz: " << baz << endl
			     << "    ka: " << ka << endl
				 << "    num test subelements: " << getNumXMLChildren("subelement/test") << endl
			     << "    subelement/test/text: " << text << endl
			     << "    subelement/test/number: " << number << endl;
			
			// change values
			baz = 666;
			ka = "Ramses II";
			text = "I am Oxymandias";
			number = 3;
			return true;
		}
	
		string name;
		float baz;
		string ka;
	
		string text;
		float number;
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
			
			cout << endl;
			cout << "ROOT: " << getXMLRootElement()->Name() << endl;
			cout << endl;
			
			cout << "ARGUMENT TEST" << endl;
			cout << "bool 1: " << getXMLAttrBool("argtest", "bool1", false) << endl
				 << "bool 0: " << getXMLAttrBool("argtest", "bool0", true) << endl
				 << "bool true:  " << getXMLAttrBool("argtest", "boolT", false) << endl
				 << "bool false: " << getXMLAttrBool("argtest", "boolF", true) << endl
				 << "int:    " << getXMLAttrInt("argtest", "int") << endl
				 << "uint:   " << getXMLAttrUInt("argtest", "uint") << endl
				 << "float:  " << getXMLAttrFloat("argtest", "float") << endl
				 << "double: " << getXMLAttrDouble("argtest", "double") << endl
				 << "string: " << getXMLAttrString("argtest", "string") << endl;
			cout << "DONE" << endl << endl;
			
			cout << "ELEMENT TEST: " << getNumXMLChildren("elementtest") << endl;
			cout << "bool 1: " << getXMLTextBool("elementtest/bool1", false) << endl
				 << "bool 0: " << getXMLTextBool("elementtest/bool0", true) << endl
				 << "bool true:  " << getXMLTextBool("elementtest/boolT", false) << endl
				 << "bool false: " << getXMLTextBool("elementtest/boolF", true) << endl
				 << "int:    " << getXMLTextInt("elementtest/int") << endl
				 << "uint:   " << getXMLTextUInt("elementtest/uint") << endl
				 << "float:  " << getXMLTextFloat("elementtest/float") << endl
				 << "double: " << getXMLTextDouble("elementtest/double") << endl
				 << "string: " << getXMLTextString("elementtest/string") << endl;
			cout << "DONE" << endl << endl;
			
			// grab elements using XMLElement directly
			XMLElement *child = getXMLChild("objecttest");
			if(child) {
				cout << "OBJECT TEST: " << getNumXMLChildren("objecttest") << endl;
				// load object class manually
				XMLElement *subchild = child->FirstChildElement();
				while(subchild != NULL) {
					Object o;
					o.loadXML(subchild); // prints here when the class readXML function called
					subchild = subchild->NextSiblingElement();
				}
				cout << "DONE" << endl << endl;
			}
			return true;
		}
	
		// derived callback, called when saving xml data from the object
		bool writeXML(XMLElement *e) {
			
			// comments
			addXMLComment("", "this is a comment");
			addXMLComment("", "\n\t\tthis is a multiline comment\n\t");
			addXMLComment("foo/bar/1", "this is a deeper comment");
			
			// write nested element text
			setXMLTextString("foo/bar/baz", "hello again");
			
			// write nested element & indices text
			setXMLTextString("foo/0/bar/1/baz/2", "guten morgen");
			
			// add an extra child at the given position, creates empty elements to fill
			XML::setTextFloat(XML::addChild(e, "foo/bar/baz", 2), 4561.23);
			
			return true;
		}
};

int main(int argc, char *argv[]) {
	cout << endl;
	
	cout << "PATH PARSING TEST" << endl;
	
	// element names
	cout << "foo/bar/baz" << endl;
	vector<XML::PathNode> nodes = XML::parsePath("foo/bar/baz");
	for(int i = 0; i < nodes.size(); ++i) {
		cout << "    " << nodes[i].name << " " << nodes[i].index << endl;
	}
	
	// element names and indices
	cout << "foo/1/bar/2/baz/3" << endl;
	nodes = XML::parsePath("foo/1/bar/2/baz/3");
	for(int i = 0; i < nodes.size(); ++i) {
		cout << "    " << nodes[i].name << " " << nodes[i].index << endl;
	}
	
	// should throw error since index comes before element name
	cout << "1/foo/bar" << endl;
	nodes = XML::parsePath("1/foo/bar");
	for(int i = 0; i < nodes.size(); ++i) {
		cout << "    " << nodes[i].name << " " << nodes[i].index << endl;
	}
	cout << "DONE" << endl << endl;
	
	// load xml file through Processor derived from XMLObject
	Processor processor;
	processor.loadXMLFile("../../data/test.xml");
	
	// add something from outside the main object
	processor.setXMLTextString("test/hello", "word boy");
	
	// save the current document, calls all objects automatically which
	// implement saveXML() and update values (key is to use XML::obtainChild
	// so as not to add extra copies of the same elements to the tree)
	processor.saveXMLFile("./testupdate.xml");
	
	// close current XML document tree
	processor.closeXMLFile();
	
	// save Object & Subobject data only since they implement saveXML() and were
	// added as children of Processor
	processor.saveXMLFile("./testsave.xml");

	return 0;
}
