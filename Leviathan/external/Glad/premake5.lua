project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "On"
	systemversion "latest"
	toolset "msc-v142"
	targetdir ("bin/%{cfg.architecture}")
	objdir ("bin-int/%{cfg.architecture}")
	architecture "x86_64"
	
	configurations 
	{
		"Debug",
		"Release"
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