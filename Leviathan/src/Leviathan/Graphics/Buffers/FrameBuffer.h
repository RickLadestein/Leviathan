#pragma once
#include "glad/glad.h"

enum class FrameBufferType {
	READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
	WRITE_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
	GENERAL_FRAMEBUFFER = GL_FRAMEBUFFER
};
class FrameBuffer {
public:
	FrameBuffer();
	FrameBuffer(FrameBufferType type);
	~FrameBuffer();
private:
	GLuint id;
	FrameBufferType type;

	void Generate();
};