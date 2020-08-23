#include "Texture.h"
#include "Leviathan/Util/FileManager.h"

int current_texture_layer_count = 0;
Texture2D::Texture2D(std::string folder_id, std::string texture_file, bool mipmap)
{
	this->handle = 0;
	this->type = TextureType::TEXTURE_2D;
	this->hasMipmap = mipmap;
	std::shared_ptr<leviathan::Image> image = leviathan::Image::Load(folder_id, texture_file);
	if (image) {
		glGenTextures(1, &this->handle);
		glBindTexture(this->handle, GL_TEXTURE_2D);
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
}

void Texture::Bind(std::weak_ptr<Texture> tex)
{
	if (current_texture_layer_count > 0)
		Texture::Unbind();

	std::shared_ptr<Texture> texture = tex.lock();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->handle);
}

void Texture::Unbind()
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
		Texture::Bind(tex);
		index += 1;
		current_texture_layer_count += 1;
		if (index == 31) // LIMIT TEXTURE SAMPLER COUNT TO 31
			break;
	}
}

void Texture::Bind()
{
	if (current_texture_layer_count > 0)
		Texture::Unbind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->handle);
}

void Texture::SetTextureWrapSetting(TextureWrapSetting s, TextureWrapSetting t)
{
	this->Bind();
	glTexParameteri((GLenum)this->type, GL_TEXTURE_WRAP_S, (GLint)s);
	glTexParameteri((GLenum)this->type, GL_TEXTURE_WRAP_T, (GLint)t);
}

void Texture::SetMinMagSetting(MinMagSetting min, MinMagSetting mag)
{
	this->Bind();
	glTexParameteri((GLenum)this->type, GL_TEXTURE_MIN_FILTER, (GLint)min);
	glTexParameteri((GLenum)this->type, GL_TEXTURE_MAG_FILTER, (GLint)mag);
}

void Texture::SetMipMapMinMagSetting(MipmapMinMagSetting min, MipmapMinMagSetting mag)
{
	this->Bind();
	if(!this->hasMipmap)
		glGenerateMipmap((GLenum)this->type);
	glTexParameteri((GLenum)this->type, GL_TEXTURE_MIN_FILTER, (GLint)min);
	glTexParameteri((GLenum)this->type, GL_TEXTURE_MAG_FILTER, (GLint)mag);
}
