#pragma once
#include "glad/glad.h"
#include "Leviathan/Graphics/Texture.h"

#include <string>
#include <memory>

namespace Leviathan::Graphics::Buffers {
	enum class FrameBufferType {
		READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
		WRITE_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER,
		GENERAL_FRAMEBUFFER = GL_FRAMEBUFFER
	};

	enum class AttatchmentType {
		COLOR_BUFFER = GL_COLOR_ATTACHMENT0,
		DEPTH_BUFFER = GL_DEPTH_ATTACHMENT,
		STENCIL_BUFFER = GL_STENCIL_ATTACHMENT,
		DEPTH_STENCIL_BUFFER = GL_DEPTH_STENCIL_ATTACHMENT
	};
	class FrameBuffer {
	public:
		FrameBuffer();
		FrameBuffer(FrameBufferType type, AttatchmentType read_buffer, int width, int height, std::string name);
		~FrameBuffer();

		void Bind();
		void Unbind();
		void Destroy();


	private:
		GLuint id;
		GLuint rbo;
		int width;
		int height;
		std::string name;
		FrameBufferType type;
		AttatchmentType attachment_type;

		void Generate();
		bool GenerateTexture();
		bool GenerateRenderBuffer();
	};
}