# xmlframework test program

# programs to build, don't install
noinst_PROGRAMS = xmltests

# bin sources, headers here because we dont want to install them
xmltests_SOURCES = main.cpp

# include paths
xmltests_CPPFLAGS = $(CXXFLAGS) $(TINYXML2_CFLAGS) -I$(top_srcdir)/src

# libs to link, set static to statically link local libtool lib
xmltests_LDFLAGS = $(TINYXML2_LIBS) -static

# local libraries needed to build (builddir), set path to .la for libtool libs
xmltests_LDADD = $(top_builddir)/src/xmlframework/libxmlframework.la
