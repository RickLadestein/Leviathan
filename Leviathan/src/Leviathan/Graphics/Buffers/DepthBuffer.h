#pragma once
#include "glad/glad.h"
enum class DepthFunc {
	ALWAYS = GL_ALWAYS,
	NEVER = GL_NEVER,
	LESS = GL_LESS,
	EQUAL = GL_EQUAL,
	LESS_EQUAL = GL_LEQUAL,
	GREATER = GL_GREATER,
	GREATER_EQUAL = GL_GEQUAL,
	NOT_EQUAL = GL_NOTEQUAL
};

class DepthBuffer {
	DepthBuffer() = delete;
	~DepthBuffer() = delete;
public:
	static void SetDepthFunction(DepthFunc func);
	static void Enable();
	static void Disable();
	static bool IsEnabled();
	static void Reset();

};