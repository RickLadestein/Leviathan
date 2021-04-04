#include "Drawable.h"
#include "Leviathan/Graphics/Shader.h"
#include "Leviathan/Graphics/Texture.h"
#include "Leviathan/Graphics/Mesh.h"
#include "Leviathan/Util/Math.h"
#include "glad/glad.h"

#include <iostream>
#include <memory>
#include <sstream>

#define SHADER_DEFAULT_NAME "default"
#define TEXTURE_DEFAULT_NAME "default"

namespace Leviathan::Graphics {
	Drawable::Drawable()
	{
		this->position = glm::vec3(0);
		this->rotation = glm::vec3(0);
		this->scale = glm::vec3(1);

		this->shader = ShaderProgram::GetShader(SHADER_DEFAULT_NAME);
		WeakTextureReference tref = TextureStorage::GetTextureById(TEXTURE_DEFAULT_NAME);
		this->texture.SetTexture(tref, 0);
	}

	Drawable::~Drawable()
	{
	}


	void Drawable::setShader(std::string shader_id)
	{
		WeakShaderReference ref = ShaderProgram::GetShader(shader_id);
		ShaderReference sref = ref.lock();
		if (sref != nullptr) {
			this->shader = ref;
		}
		else {
			std::stringstream ss;
			ss << "ShaderProgram resource " << shader_id << " does not exist";
			throw std::exception(ss.str().c_str());
		}
	}

	void Drawable::setMesh(std::string mesh_id)
	{
		WeakMeshReference ref = Leviathan::Graphics::MeshStorage::GetMesh(mesh_id);
		MeshReference mref = ref.lock();
		if (mref != nullptr) {
			this->mesh = ref;
		}
		else {
			this->mesh = WeakMeshReference();
		}
	}
}
