#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <vector>
#include <memory>
#include <string>
#include <array>

namespace Leviathan::Graphics {
	

	enum class TextureWrapSetting {
		REPEAT = GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		EDGE_CLAMP = GL_CLAMP_TO_EDGE,
		BORDER_CLAMP = GL_CLAMP_TO_BORDER
	};

	enum class MinMagSetting {
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR
	};

	enum class MipmapMinMagSetting {
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};

	enum class TextureType {
		NONE = 0x0,
		TEXTURE_1D = GL_TEXTURE_1D,
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_CUBEMAP = GL_TEXTURE_CUBE_MAP
	};

	class Texture {
	public:
		Texture() = default;
		~Texture() = default;

		virtual void Bind(bool finaltarget = true);
		virtual void Unbind(bool finaltarget = true);
		void SetTextureWrapSetting(TextureWrapSetting s, TextureWrapSetting t);
		void SetMinMagSetting(MinMagSetting min, MinMagSetting mag);
		void SetMipMapMinMagSetting(MipmapMinMagSetting min, MipmapMinMagSetting mag);
		GLuint GetHandle() { return this->handle; }

		static bool AddTexture(std::string texture_id, std::string folder_id, std::string texture_file, bool mipmap);
		static bool AddTexture(std::string texture_id, int width, int height);
		static std::weak_ptr<Texture> GetTexture(std::string id);
		static bool DeleteTexture(std::string id);
	protected:


		TextureType type = TextureType::NONE;
		int textureType;
		bool hasMipmap = false;
		bool rtg = false;
		GLuint handle = 0;
	};

	typedef std::shared_ptr<Texture> TextureReference;
	typedef std::weak_ptr<Texture> WeakTextureReference;

	class Texture1D : public Texture {
	public:
		inline Texture1D(std::string folder_id, std::string texture_file, bool mipmap = false) { throw new std::exception("Not implemented yet"); };
	};

	class Texture2D : public Texture {
	public:
		Texture2D(std::string folder_id, std::string texture_file, bool mipmap = false);
		Texture2D(int width, int height);
	};

	class Texture3D : public Texture {
	public:
		inline Texture3D(std::string folder_id, std::vector<std::string> tex_files, bool mipmap = false) { throw new std::exception("Not implemented yet"); };
	};

	class TextureCubemap : public Texture {
	public:
		inline TextureCubemap(std::string folder_id, std::string n, std::string e, std::string s, std::string w, bool mipmap = false) { throw new std::exception("Not implemented yet"); };
	};
	

#define MAX_MULTITEX_TEXTURES 8
	class MultiTexture : public Texture {
	public:
		std::array<WeakTextureReference, MAX_MULTITEX_TEXTURES> textures;

		void Bind(bool finaltarget = true) override;
		void Unbind(bool finaltarget = true) override;
	};


}



