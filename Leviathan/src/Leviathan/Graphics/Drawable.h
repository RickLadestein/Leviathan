#pragma once
#include "Leviathan/Graphics/Camera.h"
#include "Leviathan/Graphics/Buffers/VertexBuffer.h"
#include "Leviathan/Data/Object.h"

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
	class Drawable : public Object {
		friend class Renderer;
	protected:
		WeakShaderReference shader;
		MultiTexture textures;

		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 position;

		Leviathan::Graphics::Buffers::VertexBuffer vertexbuffer;

		Drawable();
		Drawable(std::string shader, std::string texture);
		Drawable(std::string shader, std::vector<std::string> textures);
		Drawable(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
		Drawable(std::string shader, std::string texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	public:
		inline void SetShader(std::string s_name) { this->shader = ShaderProgram::GetShader(s_name); }
		inline WeakShaderReference GetShader() { return this->shader; }

		inline MultiTexture* GetTextures() { return &textures; }

		inline Leviathan::Graphics::Buffers::VertexBuffer* GetVertexBuffer() { return &this->vertexbuffer; }

		inline glm::vec3 getPosition() { return this->position; }
		inline glm::vec3 getRotation() { return this->rotation; }
		inline glm::vec3 getScale() { return this->scale; }

		inline void setPosition(glm::vec3 pos) { this->position = pos; this->model_matrix_changed = true; }
		inline void setRotation(glm::vec3 rot) { this->rotation = rot; this->model_matrix_changed = true; }
		inline void setScale(glm::vec3 scale) { this->scale = scale; this->model_matrix_changed = true; }
		void setShader(std::string shader_id);

		void Translate(float x, float y, float z);
		void Translate(glm::vec3 trans);

		void RotateDegrees(float x, float y, float z);
		void RotateDegrees(glm::vec3 rot);

		void RotateRadians(float x, float y, float z);
		void RotateRadians(glm::vec3 rot);

		glm::mat4 GetModelMatrix();

		std::string ToString() override {
			std::stringstream ss;
			ss << "Drawable: ";
			return "Drawable";
		}

	private:
		bool model_matrix_changed;
		glm::mat4 model_matrix;

		void CheckRotations();

		inline void test() {}
	};
}