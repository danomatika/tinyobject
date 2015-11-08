# tinyobject library

# the library to build
lib_LTLIBRARIES = libtinyobject.la

# lib headers to install
otherincludedir = $(includedir)/$(PACKAGE)
otherinclude_HEADERS = tinyobject.h XML.h XMLObject.h

# libs sources, headers here because we dont want to install them
libtinyobject_la_SOURCES = Log.h XML.cpp XMLObject.cpp

# include paths
AM_CPPFLAGS = $(CXXFLAGS) $(TINYXML2_CFLAGS)

# libs to link
AM_LDFLAGS = $(TINYXML2_LIBS)

# make sure to remove include folder
uninstall-hook:
	if test -d ${includedir}/${PACKAGE}; then rmdir ${includedir}/${PACKAGE}; fi
