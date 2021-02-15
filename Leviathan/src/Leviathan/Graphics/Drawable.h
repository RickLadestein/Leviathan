#pragma once
#include "Leviathan/Graphics/Camera.h"
#include "Leviathan/Graphics/Buffers/VertexBuffer.h"

#include <string>
#include <sstream>
#include <vector>
#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Leviathan::Graphics {
	class Drawable {
		friend class Renderer;
	protected:
		WeakShaderReference shader;

		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 position;

		Leviathan::Graphics::Buffers::VertexBuffer vertexbuffer;
		MultiTexture texture;

		Drawable();
		~Drawable();
	public:
		inline Leviathan::Graphics::Buffers::VertexBuffer* GetVertexBuffer() { return &this->vertexbuffer; }

		inline glm::vec3 getPosition() { return this->position; }
		inline glm::vec3 getRotation() { return this->rotation; }
		inline glm::vec3 getScale() { return this->scale; }
		inline WeakShaderReference getShader() { return this->shader; }
		inline MultiTexture* getTexture() { return &texture; }

		inline void setPosition(glm::vec3 pos) { this->position = pos; this->model_matrix_changed = true; }
		inline void setRotation(glm::vec3 rot) { this->rotation = rot; this->model_matrix_changed = true; }
		inline void setScale(glm::vec3 scale) { this->scale = scale; this->model_matrix_changed = true; }
		void setShader(std::string shader_id);
		void setMesh(std::string mesh_id);

		glm::mat4 GetModelMatrix();


	private:
		bool model_matrix_changed;
		glm::mat4 model_matrix;
		std::string mesh_name;

		void CheckRotations();
		void NormalizeRotationVector(glm::vec3& rotation);

		inline void test() {}
	};
}