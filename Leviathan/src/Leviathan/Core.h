#pragma once

#ifndef GLEW_STATIC
	#define GLEW_STATIC
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