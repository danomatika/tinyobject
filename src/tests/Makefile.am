# xmlframework tests

# programs to build
noinst_PROGRAMS = xmltests

# bin sources, headers here because we dont want to install them
xmltests_SOURCES = Main.cpp

# include paths
xmltests_CPPFLAGS = $(CXXFLAGS) -I../xmlframework

# libs to link
xmltests_LDFLAGS = -L../xmlframework -lxmlframework

# move bin to bin folder after building
all-local:
	mkdir -p $(top_srcdir)/bin
	mv xmltests $(top_srcdir)/bin/xmltests

# clean bin
clean-local:
	rm -f $(top_srcdir)/bin/xmltests
