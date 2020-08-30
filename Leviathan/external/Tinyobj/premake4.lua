project "Tinyobj"
	kind "StaticLib"
	language "C++"
	staticruntime "On"
	
	targetdir ("bin/%{cfg.architecture}")
	objdir ("bin-int/%{cfg.architecture}")
	
	configurations 
	{
		"Release_x64",
		"Release_x86"
	}
	optimize "on"
    
	files
	{
		"src/tiny_obj_loader.cc",
		"include/tiny_obj_loader.h"
	}
	
	includedirs
	{
		"include"
	}
	
	filter "configurations:*86"
      architecture "x86"

	filter "configurations:*64"
      architecture "x86_64"