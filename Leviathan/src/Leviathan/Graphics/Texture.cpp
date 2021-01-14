#include "Texture.h"
#include "Leviathan/Util/FileManager.h"
#include "Leviathan/Data/Dictionary.h"
#include <unordered_map>
#include <iostream>



namespace Leviathan::Graphics {
	
	int current_texture_layer_count = 0;
	Texture* bound_texture;

	Texture2D::Texture2D(std::string folder_id, std::string texture_file, bool mipmap)
	{
		this->handle = 0;
		this->textureType = GL_TEXTURE_2D;
		this->type = TextureType::TEXTURE_2D;
		this->hasMipmap = mipmap;
		std::shared_ptr<Leviathan::Image> image = Leviathan::Image::Load(folder_id, texture_file, true);
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
		this->textureType = GL_TEXTURE_2D;
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

	void Texture::Bind(bool finaltarget)
	{
		if (finaltarget) {
			if (bound_texture != nullptr) {
				std::cerr << "Error: Trying to bind new texture while old texture is still bound" << std::endl;
				return;
			}
		}

		if (handle != GL_FALSE) {
			glBindTexture(this->textureType, this->handle);
			if (finaltarget) {
				bound_texture = this;
			}
		}
		else {
			std::cerr << "Error: Trying to bind uninitialized texture" << std::endl;
		}
	}

	void Texture::Unbind(bool finaltarget)
	{
		if (finaltarget) {
			if (bound_texture != this) {
				std::cerr << "Error: Trying to unbind not bound texture" << std::endl;
				return;
			}
		}
		if (handle != GL_FALSE) {
			glBindTexture(this->textureType, 0);
			if (finaltarget) {
				bound_texture = nullptr;
			}
		}
		else {
			std::cerr << "Error: Trying to unbind uninitialized texture" << std::endl;
		}
	}

	void Texture::SetTextureWrapSetting(TextureWrapSetting s, TextureWrapSetting t)
	{
		this->Bind();
		glTexParameteri((GLenum)this->type, GL_TEXTURE_WRAP_S, (GLint)s);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_WRAP_T, (GLint)t);
		this->Unbind();
	}

	void Texture::SetMinMagSetting(MinMagSetting min, MinMagSetting mag)
	{
		this->Bind();
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MIN_FILTER, (GLint)min);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MAG_FILTER, (GLint)mag);
		this->Unbind();
	}

	void Texture::SetMipMapMinMagSetting(MipmapMinMagSetting min, MipmapMinMagSetting mag)
	{
		this->Bind();
		if (!this->hasMipmap)
			glGenerateMipmap((GLenum)this->type);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MIN_FILTER, (GLint)min);
		glTexParameteri((GLenum)this->type, GL_TEXTURE_MAG_FILTER, (GLint)mag);
		this->hasMipmap = true;
		this->Unbind();
	}


	Leviathan::Dictionary<std::string, TextureReference> textures;
	
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
		TextureReference texture;
		bool succes = textures.try_get_value(id, texture);
		if (succes) {
			return texture;
		}
		else {
			return std::weak_ptr<Texture>();
		}
	}

	bool Texture::DeleteTexture(std::string id)
	{
		TextureReference t_ref;
		bool get_succes = textures.try_get_value(id, t_ref);
		t_ref->Unbind();
		try {
			std::weak_ptr<Texture> prg = textures.at(id);
			textures.erase(id);
			return true;
		}
		catch (std::exception e) {
			return false;
		}
	}

	
	void MultiTexture::Bind(bool finaltarget)
	{
		if (bound_texture != nullptr) {
			std::cerr << "Error: Trying to bind new texture while old texture is still bound" << std::endl;
			return;
		}
		for (unsigned int i = 0; i < textures.size(); i++) {
			
			WeakTextureReference tex = textures[i];
			TextureReference tref = tex.lock();
			if (tref != nullptr) {
				glActiveTexture(GL_TEXTURE0 + i);
				tref->Bind(false);
			}
		}
		bound_texture = this;
		glActiveTexture(GL_TEXTURE0);
	}

	void MultiTexture::Unbind(bool finaltarget)
	{
		if (bound_texture != this) {
			std::cerr << "Error: Trying to unbind not bound texture" << std::endl;
			return;
		}
		for (unsigned int i = 0; i < textures.size(); i++) {

			WeakTextureReference tex = textures[i];
			TextureReference tref = tex.lock();
			if (tref != nullptr) {
				glActiveTexture(GL_TEXTURE0 + i);
				tref->Unbind(false);
			}
		}
		bound_texture = nullptr;
		
		glActiveTexture(GL_TEXTURE0);
	}

	WeakTextureReference MultiTexture::GetTexture(int texture_layer)
	{
		if (texture_layer >= 0 && texture_layer < MAX_MULTITEX_TEXTURES) {
			return textures[texture_layer];
		}
		else {
			std::cout << "Texture layer was outside the bounds of MAX_MULTITEX_TEXTURES or negative" << std::endl;
			return WeakTextureReference();
		}
	}

	void MultiTexture::SetTexture(WeakTextureReference ref, int texture_layer)
	{
		if (bound_texture == this) {
			std::cout << "Could not set texture: Multitexture was already bound" << std::endl;
			return;
		}
		else {
			if (texture_layer >= 0 && texture_layer < MAX_MULTITEX_TEXTURES) {
				textures[texture_layer] = ref;
			}
			else {
				std::cout << "Texture layer was outside the bounds of MAX_MULTITEX_TEXTURES or negative" << std::endl;
				return;
			}
		}
	}

	void MultiTexture::SetTexture(std::string texture_id, int texture_layer) {
		WeakTextureReference tref = Texture::GetTexture(texture_id);
		this->SetTexture(tref, texture_layer);
	}
}
