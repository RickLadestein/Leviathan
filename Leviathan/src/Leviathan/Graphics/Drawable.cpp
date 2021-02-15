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
		this->model_matrix_changed = true;
		this->model_matrix = glm::mat4(1.0f);

		this->shader = ShaderProgram::GetShader(SHADER_DEFAULT_NAME);
		WeakTextureReference tref = Texture::GetTexture(TEXTURE_DEFAULT_NAME);
		this->texture.SetTexture(tref, 0);
	}

	Drawable::~Drawable()
	{
		vertexbuffer.DestroyBuffers();
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
		WeakMeshReference ref = Leviathan::Graphics::Mesh::GetMesh(mesh_id);
		MeshReference mref = ref.lock();
		if (mref != nullptr) {
			this->vertexbuffer.BufferData(mref);
		}
		else {
			std::stringstream ss;
			ss << "Mesh resouce " << mesh_id << " does not exist";
			throw std::exception(ss.str().c_str());
		}
	}

	glm::mat4 Drawable::GetModelMatrix()
	{
		if (this->model_matrix_changed) {
			/*glm::quat quaternion = EulerAnglesToQuaternion(this->rotation);
			this->model_matrix = glm::mat4(1.0f);
			this->model_matrix = glm::translate(this->model_matrix, this->position);
			this->model_matrix = glm::scale(this->model_matrix, this->scale);
			this->model_matrix *= glm::toMat4(quaternion);
			this->model_matrix_changed = false;*/

			this->model_matrix = glm::mat4(1.0f);
			this->model_matrix = glm::translate(this->model_matrix, this->position);
			//this->model_matrix = glm::translate(this->model_matrix, glm::vec3(1.0f, 0.5f, 1.0f));
			this->model_matrix = glm::scale(this->model_matrix, this->scale);

			this->model_matrix = glm::rotate(this->model_matrix, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			this->model_matrix = glm::rotate(this->model_matrix, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			this->model_matrix = glm::rotate(this->model_matrix, this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			this->model_matrix_changed = false;
		}
		return this->model_matrix;
	}

	void Drawable::CheckRotations()
	{

		bool _x = this->rotation.x >= 360.0f;
		bool _y = this->rotation.y >= 360.0f;
		bool _z = this->rotation.z >= 360.0f;
		while (_x || _y || _z) {
			if (_x) {
				this->rotation.x -= 360.0f;
			}

			if (_y) {
				this->rotation.y -= 360.0f;
			}

			if (_z) {
				this->rotation.z -= 360.0f;
			}
		}
	}

	void Drawable::NormalizeRotationVector(glm::vec3& rotation)
	{
		rotation.x = fmod(rotation.x, 360.f);
		rotation.y = fmod(rotation.y, 360.f);
		rotation.z = fmod(rotation.z, 360.f);
	}
}
