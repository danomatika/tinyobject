xmlframework
============

Copyright (c) [Dan Wilcox](http://danomatika.com) 2009, 2015

This is a wrapper around the [TinyXML-2 library](http://www.grinninglizard.com/tinyxml2/index.html) to add chainable object loading in classes and automatic loading/saving of primitive types via reference. 

See the headers in `src/xmlframework` and the example in `src/tests` for more info.

You will need tinyxml2 installed before building. On Mac OSX, you can use [Homebrew](http://brew.sh) with:

    brew install tinyxml2

This is an automake project, so build the lib & test with:

    ./configure
	make

Run the test with:

    cd src/tests
    ./xmltests
