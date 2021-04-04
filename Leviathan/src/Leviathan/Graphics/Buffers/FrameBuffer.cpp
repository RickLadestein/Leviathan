#include "FrameBuffer.h"

#include <iostream>
using Leviathan::Graphics::Texture;
namespace Leviathan::Graphics::Buffers {
	FrameBuffer::FrameBuffer()
	{
		this->id = 0;
		this->width = 100;
		this->height = 100;
		this->name = "default";
		this->rbo = 0;
		this->Generate();
	}

	FrameBuffer::FrameBuffer(int width, int height, std::string name)
	{
		this->width = width;
		this->height = height;
		this->id = 0;
		this->name = name;
		this->rbo = 0;
		this->Generate();
	}

	FrameBuffer::~FrameBuffer()
	{
		this->Destroy();
	}

	void FrameBuffer::Bind()
	{
		if (TextureStorage::GetTextureById(this->name).lock()) {
			glBindFramebuffer(GL_FRAMEBUFFER, this->id);
		}
		else {
			std::cout << "Could not bind framebuffer: target texture does not exist!" << std::endl;
		}
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Destroy()
	{
		TextureStorage::RemoveTexture(this->name);
		if (this->rbo > 0)
			glDeleteRenderbuffers(1, &this->rbo);
		if (this->id > 0) {
			glDeleteFramebuffers(1, &this->id);
		}
	}

	bool FrameBuffer::Verify()
	{
		GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		char* str;
		switch (result) {
		case GL_FRAMEBUFFER_UNDEFINED:
			str = "The specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist.";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			str = "Incomplete framebuffer attachment points";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			str = "Framebuffer does not have target texture";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			str = "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			str = "GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			str = "The combination of internal formats of the attached images violates an implementation-dependent set of restrictions";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			str = "The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers or the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			str = "Any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target";
			break;
		case GL_FRAMEBUFFER_COMPLETE:
			str = "Framebuffer is valid";
			break;
		default:
			str = "Unknown error";
			break;
		}
		std::cout << "Framebuffer error status: " << str;
		return result == GL_FRAMEBUFFER_COMPLETE;
	}

	void FrameBuffer::Generate()
	{
		glGenFramebuffers(1, &this->id);
		glBindFramebuffer(GL_FRAMEBUFFER, this->id);
		bool tex_result = this->GenerateTexture();
		bool rbuff_result = this->GenerateRenderBuffer();
		if (!this->Verify()) {
			std::cout << "Could not generate framebuffer tex = " << tex_result << " rbuff" << rbuff_result << std::endl;
			this->Destroy();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool FrameBuffer::GenerateTexture()
	{
		TextureReference tref = std::make_shared<Texture2D>(width, height);
		bool succes = TextureStorage::AddTexture(this->name, tref);
		if (succes) {
			tref->Bind();
			tref->SetMinMagSetting(MinMagSetting::LINEAR, MinMagSetting::LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_FRAMEBUFFER, GL_TEXTURE_2D, tref->GetHandle(), 0);
		}
		return succes;
	}

	bool FrameBuffer::GenerateRenderBuffer()
	{
		glGenRenderbuffers(1, &this->rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->width, this->height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		return this->rbo > 0;
	}
}
