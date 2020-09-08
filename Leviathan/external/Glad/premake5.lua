project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	systemversion "latest"
	toolset "msc-v142"
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
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}
	
	includedirs
	{
		"include"
	}
	
	filter "configurations:*86"
      architecture "x86"

	filter "configurations:*64"
      architecture "x86_64"