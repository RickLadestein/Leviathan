workspace "Leviathan"
	configurations 
	{
		"Debug_x86",
		"Release_x86",
		"Debug_x64",
		"Release_x64"
	}
    filter "configurations:*86"
      architecture "x86"

	filter "configurations:*64"
      architecture "x86_64"

outputdir = "%{prj.name}/%{cfg.buildcfg}"
IncludeDir = {}
IncludeDir["Glfw"] = "Leviathan/external/Glfw/include"
IncludeDir["Glad"] = "Leviathan/external/Glad/include"
IncludeDir["Leviathan"] = "Leviathan/src"


group "Dependencies"
	include "Leviathan/external/Glad"
	include "Leviathan/external/Glfw"
group ""

project "Leviathan"
	location "Leviathan"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	systemversion "latest"
	toolset "msc-v142"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/")
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/external/include",
		"%{prj.name}/external/Glad/include",
		"%{prj.name}/external/Glfw/include",
		"%{prj.name}/external/Tinyobj",
		"%{prj.name}/src"
	}
	
	defines
	{
		"LV_PLATFORM_WINDOWS",
		"STB_IMAGE_IMPLEMENTATION",
		"TINYOBJLOADER_IMPLEMENTATION",
		"GLFW_INCLUDE_NONE"
	}
	
	
	filter "configurations:*86"
		libdirs {"%{prj.name}/external/libs/%{cfg.architecture}"}
		links 
		{
			"opengl32.lib",
			"Glad",
			"Glfw"
		}
		
		
	filter "configurations:*64"
		libdirs {"%{prj.name}/external/libs/%{cfg.architecture}"}
		links 
		{
			"opengl32.lib",
			"Glad",
			"Glfw"
		}
	
	
	
	filter "configurations:Debug_x86"
		defines "LV_DEBUG"
		symbols "On"
	filter "configurations:Release_x86"
		defines "LV_RELEASE"
		optimize "On"
	filter "configurations:Debug_x64"
		defines "LV_DEBUG"
		symbols "On"
	filter "configurations:Release_x64"
		defines "LV_RELEASE"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	
	targetdir ("bin/" .. outputdir .. "/")
	objdir ("bin-int/" .. outputdir .. "/")
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/external/include",
		"Leviathan/src",
		"Leviathan/external/include",
		"Leviathan/external/Glad/include",
		"Leviathan/external/Glfw/include"
	}
	
	defines
	{
		"LV_PLATFORM_WINDOWS",
		"GLFW_INCLUDE_NONE"
	}
	
	links 
	{
		"Leviathan"
	}
	
	filter "configurations:Debug_x86"
		defines "LV_DEBUG"
		symbols "On"
	filter "configurations:Release_x86"
		defines "LV_RELEASE"
		optimize "On"
	filter "configurations:Debug_x64"
		defines "LV_DEBUG"
		symbols "On"
	filter "configurations:Release_x64"
		defines "LV_RELEASE"
		optimize "On"
	