#include "FrameBuffer.h"

#include <iostream>
using Leviathan::Graphics::Texture;
namespace Leviathan::Graphics::Buffers {
	FrameBuffer::FrameBuffer()
	{
		this->id = 0;
		this->type = FrameBufferType::GENERAL_FRAMEBUFFER;
		this->width = 100;
		this->height = 100;
		this->name = "default";
		this->rbo = 0;
		this->Generate();
	}

	FrameBuffer::FrameBuffer(FrameBufferType type, AttatchmentType read_buffer, int width, int height, std::string name)
	{
		this->width = width;
		this->height = height;
		this->id = 0;
		this->type = type;
		this->name = name;
		this->rbo = 0;
		this->attachment_type = read_buffer;
		this->Generate();
	}

	FrameBuffer::~FrameBuffer()
	{
		this->Destroy();
	}

	void FrameBuffer::Bind()
	{
		if (Texture::GetTexture(this->name).lock()) {
			glBindFramebuffer((GLenum)this->type, this->id);
		}
		else {
			std::cout << "Could not bind framebuffer: underlying texture does not exist!" << std::endl;
		}
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Destroy()
	{
		Texture::DeleteTexture(this->name);
		if (this->rbo > 0)
			glDeleteRenderbuffers(1, &this->rbo);
		if (this->id > 0) {
			glDeleteFramebuffers(1, &this->id);
		}
	}

	void FrameBuffer::Generate()
	{
		glGenFramebuffers(1, &this->id);
		glBindFramebuffer((GLenum)this->type, this->id);
		bool tex_result = this->GenerateTexture();
		bool rbuff_result = this->GenerateRenderBuffer();
		if (glCheckFramebufferStatus((GLenum)this->type) == GL_FRAMEBUFFER_COMPLETE) {

		}
		else {
			std::cout << "Could not generate framebuffer tex = " << tex_result << " rbuff" << rbuff_result << std::endl;
			this->Destroy();
		}
		glBindFramebuffer((GLenum)this->type, 0);
	}

	bool FrameBuffer::GenerateTexture()
	{
		bool succes = Texture::AddTexture(this->name, this->width, this->height);
		if (succes) {
			std::shared_ptr<Texture> tex = Texture::GetTexture(this->name).lock();
			tex->SetMinMagSetting(MinMagSetting::LINEAR, MinMagSetting::LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)this->attachment_type, GL_TEXTURE_2D, tex->GetHandle(), 0);
		}
		return succes;
	}

	bool FrameBuffer::GenerateRenderBuffer()
	{
		glGenRenderbuffers(1, &this->rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
		switch (this->attachment_type) {
		case AttatchmentType::COLOR_BUFFER:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, this->width, this->height);
			break;
		case AttatchmentType::DEPTH_BUFFER:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, this->width, this->height);
			break;
		case AttatchmentType::STENCIL_BUFFER:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, this->width, this->height);
			break;
		case AttatchmentType::DEPTH_STENCIL_BUFFER:
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->width, this->height);
			break;
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, (GLenum)this->attachment_type, GL_RENDERBUFFER, rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		return this->rbo > 0;
	}
}
