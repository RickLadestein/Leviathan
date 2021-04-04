#pragma once
#include "Leviathan/Graphics/Camera.h"
#include "Leviathan/Graphics/Buffers/VertexBuffer.h"

#include <string>
#include <sstream>
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Leviathan/Data/Transform.h"
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

		WeakMeshReference mesh;
		MultiTexture texture;

		Drawable();
		~Drawable();
	public:
		Leviathan::Data::Transform transform;

		inline glm::vec3 getPosition() { return this->position; }
		inline glm::vec3 getRotation() { return this->rotation; }
		inline glm::vec3 getScale() { return this->scale; }
		inline WeakShaderReference getShader() { return this->shader; }
		inline MultiTexture* getTexture() { return &texture; }
		inline WeakMeshReference getMesh() { return this->mesh; }


		void setShader(std::string shader_id);
		void setMesh(std::string mesh_id);
	private:
		std::string mesh_name;
	};
}