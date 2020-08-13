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

project "Leviathan"
	location "Leviathan"
	kind "SharedLib"
	language "C++"
	
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
		"%{prj.name}/src"
	}
	
	defines
	{
		"LV_PLATFORM_WINDOWS",
		"LV_BUILD_DLL",
		"_WINDLL"
	}
	
	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} %{wks.location}/bin/Sandbox/%{cfg.buildcfg}")
	}
	
	
	filter "configurations:*86"
		libdirs {"%{prj.name}/external/libs/%{cfg.architecture}"}
		links 
		{
			"opengl32.lib",
			"glew32.lib",
			"glfw3.lib"
			
		}
		
		
	filter "configurations:*64"
		libdirs {"%{prj.name}/external/libs/%{cfg.architecture}"}
		links 
		{
			"opengl32.lib",
			"glew32.lib",
			"glfw3.lib"
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
		"Leviathan/external/include"
	}
	
	defines
	{
		"LV_PLATFORM_WINDOWS"
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
	