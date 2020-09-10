#pragma once
#include "glad/glad.h"
enum class StencilOp {
	KEEP = GL_KEEP,
	ZERO = GL_ZERO,
	REPLACE = GL_REPLACE,
	INCREMENT = GL_INCR,
	INCREMENT_WRAP = GL_INCR_WRAP,
	DECREMENT = GL_DECR,
	DECREMENT_WRAP = GL_DECR_WRAP,
	INVERT = GL_INVERT
};

enum class StencilFunc {
	NEVER = GL_NEVER,
	LESS = GL_LESS,
	LESS_EQUAL = GL_LEQUAL,
	GREATER = GL_GREATER,
	GREATER_EQUAL = GL_GEQUAL,
	EQUAL = GL_EQUAL,
	NOT_EQUAL = GL_NOTEQUAL,
	ALWAYS = GL_ALWAYS
};
class StencilBuffer
{
	StencilBuffer() = delete;
	~StencilBuffer() = delete;

public:
	static void SetStencilOperation(StencilOp stencil_fail, StencilOp depth_fail, StencilOp depth_pass);
	static void SetStencilFunc(StencilFunc func, GLint ref, GLuint mask);
	static void SetStencilWritePerm(bool write);
	static bool IsEnabled();
	static void Enable();
	static void Disable();
	static void Reset();


};