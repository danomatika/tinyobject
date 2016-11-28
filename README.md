tinyobject
==========

object base class and convenience static class for TinyXML-2

Copyright (c) [Dan Wilcox](http://danomatika.com) 2009, 2015

Description
-----------

This is a wrapper around the [TinyXML-2 library](http://www.grinninglizard.com/tinyxml2/index.html) to add chainable object loading in classes and automatic loading/saving of primitive types via reference (XMLObject). Also includes a static class (XML) for common data get/set convenience functions. Both classes utilize the "tinyxml" namespace.

Documentation
-------------

See the headers in `src/tinyobject` and the [example](https://github.com/danomatika/tinyobject/blob/master/src/totest/main.cpp) in `src/totest` for more info.

Building & Installing
---------------------

Download a release tarball from <http://docs.danomatika.com/releases/tinyobject/>.

Otherwise, if cloning this repo, you will also need to run `autogen.sh` to create the configure script:

    git clone https://github.com/danomatika/tinyobject.git
    cd tinyobject
    ./autogen.sh

You will need tinyxml2 installed before building. On macOS, you can use [Homebrew](http://brew.sh) with:

    brew install tinyxml2

On Ubuntu/Debian, you would do the following:

    sudo apt-get install libtinyxml2-dev

This is an automake project, so build the lib & test with:

    ./configure
	make

Run the test program with:

    cd src/totest
    ./totest

Install via:

    sudo make install

Developing
----------

A Premake4 script and IDE files can be found in the prj folder. Premake4 can generate IDE files from a given lua script. Download Premake4 from <http://industriousone.com/premake>.

You can enable a debug build using:

    ./configure --enable-debug

I develop using an IDE, then update the autotools files when the sources are finished. I run `make distcheck` to make sure the distributable package can be built successfully.

Notes
-----

_Note: tinyobject was originally named "xmlframework" in versions prior to 0.3.0_
