#include "Texture.h"
#include "Leviathan/Util/FileManager.h"
#include "Leviathan/Data/Dictionary.h"
#include <unordered_map>
#include <iostream>
#include <sstream>



namespace Leviathan::Graphics {
	
	int current_texture_layer_count = 0;
	MultiTexture* bound_texture;
	const int t_units[8] = { GL_TEXTURE0,  GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7 };

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

	void Texture::Bind()
	{
		if (handle != GL_FALSE) {
			glBindTexture(this->textureType, this->handle);
		}
		else {
			std::cerr << "Error: Trying to bind uninitialized texture" << std::endl;
		}
	}

	void Texture::Unbind()
	{
		if (handle != GL_FALSE) {
			glBindTexture(this->textureType, 0);
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

	
	
	void MultiTexture::Bind()
	{
		if (bound_texture != nullptr) {
			std::cerr << "Error: Trying to bind new multitexture while old multitexture is still bound" << std::endl;
			return;
		}
		for (unsigned int i = 0; i < MAX_MULTITEX_TEXTURES; i++) {
			
			WeakTextureReference tex = textures[i];
			TextureReference tref = tex.lock();
			if (tref != nullptr) {
				glActiveTexture(t_units[i]);
				tref->Bind();
			}
		}
		bound_texture = this;
		glActiveTexture(GL_TEXTURE0);
	}

	void MultiTexture::Unbind()
	{
		if (bound_texture != this) {
			std::cerr << "Error: Trying to unbind not bound multitexture" << std::endl;
			return;
		}
		for (unsigned int i = 0; i < MAX_MULTITEX_TEXTURES; i++) {

			WeakTextureReference tex = textures[i];
			TextureReference tref = tex.lock();
			if (tref != nullptr) {
				glActiveTexture(t_units[i]);
				tref->Unbind();
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
				std::stringstream ss;
				ss << "texture_" << texture_layer;
				texture_names[texture_layer] = ss.str();
			}
			else {
				std::cout << "Texture layer was outside the bounds of MAX_MULTITEX_TEXTURES or negative" << std::endl;
				return;
			}
		}
	}

	void MultiTexture::SetTexture(std::string texture_id, int texture_layer) {
		WeakTextureReference tref = TextureStorage::GetTextureById(texture_id);
		this->SetTexture(tref, texture_layer);
	}

	Leviathan::Dictionary<std::string, TextureReference> texture_storage;

	WeakTextureReference TextureStorage::GetTextureById(std::string texture_id)
	{
		TextureReference found_texture;
		texture_storage.try_get_value(texture_id, found_texture);
		return found_texture;
	}
	bool TextureStorage::AddTexture(std::string texture_id, TextureReference texture_ref)
	{
		TextureReference found_texture;
		texture_storage.try_get_value(texture_id, found_texture);
		if (found_texture == nullptr) {
			//Texture does not exist yet
			texture_storage[texture_id] = texture_ref;
			return true;
		}
		else {
			//Texture exists
			throw std::exception("A texture with that id already exists");
			return false;
		}
	}
	bool TextureStorage::RemoveTexture(std::string texture_id)
	{
		return texture_storage.try_erase(texture_id);
	}
}
