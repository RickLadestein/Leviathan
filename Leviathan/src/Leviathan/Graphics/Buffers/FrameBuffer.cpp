#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	this->id = 0;
	this->type = FrameBufferType::GENERAL_FRAMEBUFFER;
	this->Generate();
}

FrameBuffer::FrameBuffer(FrameBufferType type)
{
	this->id = 0;
	this->type = type;
	this->Generate();
}

FrameBuffer::~FrameBuffer()
{
	if (this->id > 0) {
		glDeleteFramebuffers(1, &this->id);
	}
}

void FrameBuffer::Generate()
{
	glGenFramebuffers(1, &this->id);
	glBindFramebuffer((GLenum)this->type, this->id);

	if (glCheckFramebufferStatus((GLenum)this->type) == GL_FRAMEBUFFER_COMPLETE) {

	}
}
