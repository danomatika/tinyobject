# xmlframework library

# the library to build
lib_LTLIBRARIES = libxmlframework.la

# lib headers to install
otherincludedir = $(includedir)/$(PACKAGE)
otherinclude_HEADERS = xmlframework.h Xml.h XmlObject.h

# libs sources, headers here because we dont want to install them
libxmlframework_la_SOURCES = Log.h Xml.cpp XmlObject.cpp

# include paths
AM_CPPFLAGS = $(CXXFLAGS) $(TINYXML2_CFLAGS)

# libs to link
AM_LDFLAGS = $(TINYXML2_LIBS)

# make sure to remove include folder
uninstall-hook:
	if test -d ${includedir}/${PACKAGE}; then rmdir ${includedir}/${PACKAGE}; fi
