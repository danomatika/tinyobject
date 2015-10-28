--[[ A solution contains projects, and defines the available configurations

http://industriousone.com/premake/user-guide

example: http://opende.svn.sourceforge.net/viewvc/opende/trunk/build/premake4.lua?revision=1708&view=markup

http://bitbucket.org/anders/lightweight/src/tip/premake4.lua

]]
solution "xmlframework"
	configurations { "Debug", "Release" }
	objdir "../obj"
 
-- oscframework library
project "xmlframework"
	kind "StaticLib"
	language "C++"
	targetdir "../src/xmlframework"
	files { "../src/xmlframework/**.h", "../src/xmlframework/**.cpp" }

	configuration "linux"
		buildoptions { "`pkg-config --cflags tinyxml2`" }
		linkoptions { "`pkg-config --libs tinyxml2`" }

	configuration "macosx"
		-- Homebrew & MacPorts
		includedirs { "/usr/local/include", "/opt/local/include"}
		libdirs { "/usr/local/lib", "/opt/local/lib" }
		buildoptions { "-fvisibility=default" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" } 

-- test executable
project "xmltests"
	kind "ConsoleApp"
	language "C++"
	targetdir "../src/tests"
	files { "../src/tests/**.h", "../src/tests/**.cpp" }

	includedirs { "../src" }
	links { "xmlframework" }

	configuration "linux"
		buildoptions { "`pkg-config --cflags tinyxml2`" }
		linkoptions { "`pkg-config --libs tinyxml2`" }

	configuration "macosx"
		-- Homebrew & MacPorts
		includedirs { "/usr/local/include", "/opt/local/include"}
		libdirs { "/usr/local/lib", "/opt/local/lib" }
		buildoptions { "-fvisibility=default" }
		links { "tinyxml2" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
		
