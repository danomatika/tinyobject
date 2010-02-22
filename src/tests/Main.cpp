
#include <xmlframework.h>
#include <iostream>

using namespace std;
using namespace xml;

int main(int argc, char *argv[])
{
    cout << "starting xmlframework test" << endl;
    
    string file = "../data/test.xml";

    TiXmlDocument xmlDoc;
    xmlDoc.LoadFile(file);
    TiXmlElement* xml = xmlDoc.FirstChildElement();
    if(xml == NULL)
    {
        cout << "    Failed to load \"" << file << "\"" << endl;
        return -1;
    }
    cout << "    Loaded \"" << file << "\"" << endl;

    // check if the root is correct
    if(xml->ValueStr() != "poetry")
    {
        cout << "    Doc Root \"" << xml->ValueStr() << "\" != \"poetry\"" << endl;
        return -1;
    }

    // just print whatever children are there
    TiXmlElement* child = xml->FirstChildElement();
    while(child != NULL)
    {
        cout << child->ValueStr() << ": " << child->GetText() << endl;
        child = child->NextSiblingElement();
    }

    cout << endl;
	
    cout << "exited cleanly" << endl;

    return 0;
}
