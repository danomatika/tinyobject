# xmlframework library

# some source files are in a subdir
AUTOMAKE_OPTIONS = subdir-objects

# the library to build
lib_LTLIBRARIES = libxmlframework.la

# lib headers to install
otherincludedir = $(includedir)/$(PACKAGE)
otherinclude_HEADERS = xmlframework.h Xml.h XmlObject.h

# libs sources, headers here because we dont want to install them
libxmlframework_la_SOURCES = Log.h \
                             Xml.cpp \
                             XmlObject.cpp \
                             tinyxml/tinystr.h \
                             tinyxml/tinystr.cpp \
                             tinyxml/tinyxml.h \
                             tinyxml/tinyxml.cpp \
                             tinyxml/tinyxmlerror.cpp \
                             tinyxml/tinyxmlparser.cpp

# include paths
AM_CPPFLAGS = $(CXXFLAGS)

# libs to link
AM_LDFLAGS =

# make sure to remove include folder
uninstall-hook:
	if test -d ${includedir}/${PACKAGE}; then rmdir ${includedir}/${PACKAGE}; fi
