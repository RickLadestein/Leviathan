#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <vector>
#include <memory>
#include <string>
#include <array>

namespace Leviathan::Graphics {
	
	/// <summary>
	/// Enum specifying the texture wrapping settings
	/// </summary>
	enum class TextureWrapSetting {
		/// <summary>
		/// Use repeat for outside mode of bounds texture mapping
		/// </summary>
		REPEAT = GL_REPEAT,

		/// <summary>
		/// Use mirrored repeat mode for outside of bounds texture mapping
		/// </summary>
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,

		/// <summary>
		/// Use edge clamp mode for outside of bounds texture mapping
		/// </summary>
		EDGE_CLAMP = GL_CLAMP_TO_EDGE,

		/// <summary>
		/// Use edge clamp mode for outside of bounds texture mapping
		/// </summary>
		BORDER_CLAMP = GL_CLAMP_TO_BORDER
	};

	/// <summary>
	/// Enum specifying the mini/magnification setting
	/// </summary>
	enum class MinMagSetting {
		/// <summary>
		/// Use nearest neighbour pixel filtering for mini/magnification 
		/// </summary>
		NEAREST = GL_NEAREST,

		/// <summary>
		/// Use linear pixel filtering for mini/magnification 
		/// </summary>
		LINEAR = GL_LINEAR
	};

	/// <summary>
	/// Enum specifying the mipmap minification and magnification setting
	/// </summary>
	enum class MipmapMinMagSetting {
		/// <summary>
		/// Use nearest neighbour pixel filtering for mipmap mini/magnification 
		/// </summary>
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		
		/// <summary>
		/// Use linear pixel filtering for mipmap minification and use nearest neighbour pixel filtering for mipmap magnification 
		/// </summary>
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,

		/// <summary>
		/// Use nearest neighbour pixel filtering for mipmap minification and  use linear pixel filtering for mipmap magnificationfication
		/// </summary>
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,

		/// <summary>
		/// Use linear pixel filtering for mipmap mini/magnification 
		/// </summary>
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};

	/// <summary>
	/// Enum specifying the type of texture
	/// </summary>
	enum class TextureType {
		/// <summary>
		/// Texture has no type
		/// </summary>
		NONE = 0x0,

		/// <summary>
		/// 1 dimensional texture type
		/// </summary>
		TEXTURE_1D = GL_TEXTURE_1D,

		/// <summary>
		/// 2 dimensional texture type
		/// </summary>
		TEXTURE_2D = GL_TEXTURE_2D,

		/// <summary>
		/// Cubemap texture type
		/// </summary>
		TEXTURE_CUBEMAP = GL_TEXTURE_CUBE_MAP
	};

	/// <summary>
	/// Enum specifying the layer of the texture
	/// starting from the bottom <c>TextureLayer::FIRST</c> to the top most <c>TextureLayer::EIGHTH</c>
	/// </summary>
	enum class TextureLayer {
		/// <summary>
		/// Texture layer number 1
		/// </summary>
		FIRST = 0x0,

		/// <summary>
		/// Texture layer number 2
		/// </summary>
		SECOND = 0x1,

		/// <summary>
		/// Texture layer number 3
		/// </summary>
		THIRD = 0x2,

		/// <summary>
		/// Texture layer number 4
		/// </summary>
		FOURTH = 0x3,

		/// <summary>
		/// Texture layer number 5
		/// </summary>
		FIFTH = 0x4,

		/// <summary>
		/// Texture layer number 6
		/// </summary>
		SIXTH = 0x5,

		/// <summary>
		/// Texture layer number 7
		/// </summary>
		SEVENTH = 0x6,

		/// <summary>
		/// Texture layer number 8
		/// </summary>
		EIGHTH = 0x7
	};

	class Texture {
	public:
		Texture() = default;
		~Texture() = default;

		virtual void Bind();
		virtual void Unbind();
		void SetTextureWrapSetting(TextureWrapSetting s, TextureWrapSetting t);
		void SetMinMagSetting(MinMagSetting min, MinMagSetting mag);
		void SetMipMapMinMagSetting(MipmapMinMagSetting min, MipmapMinMagSetting mag);
		GLuint GetHandle() { return this->handle; }
	protected:


		TextureType type = TextureType::NONE;
		int textureType = 0;
		bool hasMipmap = false;
		bool rtg = false;
		GLuint handle = 0;
	};

	typedef std::shared_ptr<Texture> TextureReference;
	typedef std::weak_ptr<Texture> WeakTextureReference;

	class Texture2D : public Texture {
	public:
		Texture2D(std::string folder_id, std::string texture_file, bool mipmap = false);
		Texture2D(int width, int height);
	};

	class TextureCubemap : public Texture {
	public:
		inline TextureCubemap(std::string folder_id, std::string n, std::string e, std::string s, std::string w, bool mipmap = false) { throw new std::exception("Not implemented yet"); };
	};
	

#define MAX_MULTITEX_TEXTURES 8
	class MultiTexture {
	public:
		std::array<WeakTextureReference, MAX_MULTITEX_TEXTURES> textures;
		std::array<std::string, MAX_MULTITEX_TEXTURES> texture_names;

		MultiTexture() {
			for (int i = 0; i < MAX_MULTITEX_TEXTURES; i++) {
				texture_names[i] = "";
			}
		}

		WeakTextureReference& operator[](unsigned int index) {
			return textures[index];
		}

		void Bind();
		void Unbind();

		void SetTexture(WeakTextureReference ref, int texture_layer);
		void SetTexture(std::string texture_id, int texture_layer);
		WeakTextureReference GetTexture(int texture_layer);
	};

	class TextureStorage {
		TextureStorage() = delete;
		~TextureStorage() = delete;
	public:
		static WeakTextureReference GetTextureById(std::string texture_id);
		static bool AddTexture(std::string texture_id, TextureReference texture_ref);
		static bool RemoveTexture(std::string texture_id);
	};
}






