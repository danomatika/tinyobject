--[[ A solution contains projects, and defines the available configurations

http://industriousone.com/premake/user-guide

example: http://opende.svn.sourceforge.net/viewvc/opende/trunk/build/premake4.lua?revision=1708&view=markup

http://bitbucket.org/anders/lightweight/src/tip/premake4.lua

]]
solution "tinyobject"
	configurations { "Debug", "Release" }
	objdir "obj"
 
-- tinyobject library
project "tinyobject"
	kind "StaticLib"
	language "C++"
	targetdir "../src/tinyobject"
	files { "../src/tinyobject/**.h", "../src/tinyobject/**.cpp" }

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
project "totest"
	kind "ConsoleApp"
	language "C++"
	targetdir "../src/totest"
	files { "../src/totest/**.h", "../src/totest/**.cpp" }

	includedirs { "../src" }
	links { "tinyobject" }

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
		
