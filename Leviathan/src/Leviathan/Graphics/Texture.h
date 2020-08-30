#pragma once
#include "Leviathan/Core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <memory>
#include <string>

enum class LEVIATHAN_API TextureWrapSetting{
	REPEAT = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	EDGE_CLAMP = GL_CLAMP_TO_EDGE,
	BORDER_CLAMP = GL_CLAMP_TO_BORDER
};

enum class LEVIATHAN_API MinMagSetting {
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR
};

enum class LEVIATHAN_API MipmapMinMagSetting {
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

enum class LEVIATHAN_API TextureType {
	NONE = 0x0,
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_CUBEMAP = GL_TEXTURE_CUBE_MAP
};

class LEVIATHAN_API Texture {
public:
	Texture() = default;
	~Texture() = default;

	static void bind(std::weak_ptr<Texture> tex);
	static void unbind();
	static void BindMultiTex(std::vector<std::weak_ptr<Texture>>* textures);

	void bind();
	void SetTextureWrapSetting(TextureWrapSetting s, TextureWrapSetting t);
	void SetMinMagSetting(MinMagSetting min, MinMagSetting mag);
	void SetMipMapMinMagSetting(MipmapMinMagSetting min, MipmapMinMagSetting mag);

	static bool AddTexture(std::string texture_id, std::string folder_id, std::string texture_file, bool mipmap);
	static std::weak_ptr<Texture> GetTexture(std::string id);
	static bool DeleteTexture(std::string id);
protected:
	

	TextureType type = TextureType::NONE;
	bool hasMipmap = false;
	bool rtg = false;
	GLuint handle = 0;
};

class LEVIATHAN_API Texture1D : public Texture {
public:
	inline Texture1D(std::string folder_id, std::string texture_file, bool mipmap = false) { throw new std::exception("Not implemented yet"); };
};

class LEVIATHAN_API Texture2D : public Texture {
public:
	Texture2D(std::string folder_id, std::string texture_file, bool mipmap = false);
};

class LEVIATHAN_API Texture3D : public Texture {
public:
	inline Texture3D(std::string folder_id, std::vector<std::string> tex_files, bool mipmap = false) { throw new std::exception("Not implemented yet"); };
};

class LEVIATHAN_API TextureCubemap : public Texture {
public:
	inline TextureCubemap(std::string folder_id, std::string n, std::string e, std::string s, std::string w, bool mipmap = false) { throw new std::exception("Not implemented yet"); };
};



