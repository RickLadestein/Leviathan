#pragma once
#include "glad/glad.h"
#include "Leviathan/Graphics/Texture.h"

#include <string>
#include <memory>

#ifdef LEVIATHAN_DEBUG
#define FB_DEBUG() (__debugbreak()) 
#else
#define FB_DEBUG() (0)
#endif

namespace Leviathan::Graphics::Buffers {
	class FrameBuffer {
	public:
		FrameBuffer();
		FrameBuffer(int width, int height, std::string name);
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

		void Generate();
		bool GenerateTexture();
		bool GenerateRenderBuffer();
		bool Verify();
	};
}