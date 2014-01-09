xmlframework
============

Copyright (c) [Dan Wilcox](http://danomatika.com) 2009,2010

This is a wrapper around the [TinyXML library](http://www.grinninglizard.com/tinyxml/index.html) to add chainable object loading in classes and automatic loading/saving of primitive types via reference. 

See the headers in `src/xmlframework` and the example in `src/tests` for more info.

This is an automake project, so build the lib & test with:

    ./configure
	make

Run the test with:

    cd src/tests
    ./xmltests

