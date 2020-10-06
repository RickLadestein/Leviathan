#include "Texture.h"
#include "Leviathan/Util/FileManager.h"

#include <unordered_map>

namespace Leviathan::Graphics {
	int current_texture_layer_count = 0;
	Texture2D::Texture2D(std::string folder_id, std::string texture_file, bool mipmap)
	{
		this->handle = 0;
		this->type = TextureType::TEXTURE_2D;
		this->hasMipmap = mipmap;
		std::shared_ptr<leviathan::Image> image = leviathan::Image::Load(folder_id, texture_file);
		if (image) {
			glGenTextures(1, &this->handle);
			glBindTexture(GL_TEXTURE_2D, this->handle);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			int nrChannels = image->GetChannelCount();
			int width, height;
			unsigned char* data = image->GetDataPtr();
			image->GetDimensions(&width, &height);

			if (nrChannels == 3) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			else if (nrChannels == 4) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			}
			if (mipmap) {
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		}
		this->rtg = true;
	}

	Texture2D::Texture2D(int width, int height)
	{
		this->handle = 0;
		this->type = TextureType::TEXTURE_2D;
		this->hasMipmap = false;
		glGenTextures(1, &this->handle);
		glBindTexture(GL_TEXTURE_2D, this->handle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		this->rtg = true;
	}

	void Texture::bind(std::weak_ptr<Texture> tex)
	{
		if (current_texture_layer_count > 0)
			Texture::unbind();

		std::shared_ptr<Texture> texture = tex.lock();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->handle);
	}

	void Texture::unbind()
	{
		for (int i = 0; i < current_texture_layer_count; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		current_texture_layer_count = 0;
	}

	void Texture::BindMultiTex(std::vector<std::weak_ptr<Texture>>* textures)
	{
		int index = 0;
		for each (std::weak_ptr<Texture> tex in *textures)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			Texture::bind(tex);
			index += 1;
			current_texture_layer_count += 1;
			if (index == 31) // LIMIT TEXTURE SAMPLER COUNT TO 31
				break;
		}
	}

	void Texture::bind()
	{
		if (current_texture_layer_count > 0)
			Texture::unbind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->handle);
	}

	void Texture::SetTextureWrapSetting(TextureWrapSetting s, TextureWrapSetting t)
	{
		this->bind();
		glTexParameteri((GLenum)this->type, GL_TEXTURE_WRAP_S, (GLint)s);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_WRAP_T, (GLint)t);
	}

	void Texture::SetMinMagSetting(MinMagSetting min, MinMagSetting mag)
	{
		this->bind();
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MIN_FILTER, (GLint)min);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MAG_FILTER, (GLint)mag);
	}

	void Texture::SetMipMapMinMagSetting(MipmapMinMagSetting min, MipmapMinMagSetting mag)
	{
		this->bind();
		if (!this->hasMipmap)
			glGenerateMipmap((GLenum)this->type);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MIN_FILTER, (GLint)min);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MAG_FILTER, (GLint)mag);
	}


	std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
	bool Texture::AddTexture(std::string texture_id, std::string folder_id, std::string texture_file, bool mipmap)
	{
		try {
			if (textures.at(texture_id)) {
				return false;
			}
		}
		catch (std::exception e) {
			std::shared_ptr<Texture> tex = std::make_shared<Texture2D>(folder_id, texture_file, mipmap);
			if (tex->rtg) {
				textures[texture_id] = tex;
				return true;
			}
		}
		return false;
	}

	bool Texture::AddTexture(std::string texture_id, int width, int height)
	{
		try {
			if (textures.at(texture_id)) {
				return false;
			}
		}
		catch (std::exception e) {
			std::shared_ptr<Texture> tex = std::make_shared<Texture2D>(width, height);
			if (tex->rtg) {
				textures[texture_id] = tex;
				return true;
			}
		}
		return false;
	}

	std::weak_ptr<Texture> Texture::GetTexture(std::string id)
	{
		try {
			return textures.at(id);
		}
		catch (std::exception e) {
			return std::weak_ptr<Texture>();
		}
	}

	bool Texture::DeleteTexture(std::string id)
	{
		try {
			std::weak_ptr<Texture> prg = textures.at(id);
			textures.erase(id);
			return true;
		}
		catch (std::exception e) {
			return false;
		}
	}
}
