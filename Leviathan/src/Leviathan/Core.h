#pragma once
#ifndef STB_IMAGE_IMPLEMENTATION
	#define STB_IMAGE_IMPLEMENTATION
#endif

#ifdef LV_PLATFORM_WINDOWS
	#ifdef LV_BUILD_DLL
		#define LEVIATHAN_API __declspec(dllexport)
	#else
		#define LEVIATHAN_API __declspec(dllimport)
	#endif
#else
	#error Leviathan engine currently only supports windows!
#endif
