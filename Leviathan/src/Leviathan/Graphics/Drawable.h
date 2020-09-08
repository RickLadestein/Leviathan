#pragma once
#include "Leviathan/Core.h"
#include <string>
#include <glm/glm.hpp>
#include "Leviathan/Graphics/VertexBuffer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

template struct LEVIATHAN_API glm::vec<3, float, glm::packed_highp>;
template struct LEVIATHAN_API glm::vec<4, float, glm::packed_highp>;
template struct LEVIATHAN_API glm::mat<4, 4, glm::f32, glm::packed_highp>;
class LEVIATHAN_API Drawable {
protected:
	const char* shader;
	const char* texture;

	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 position;

	VertexBuffer vertexbuffer;

	Drawable();
	Drawable(std::string shader, std::string texture);
	Drawable(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Drawable(std::string shader, std::string texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
public:
	inline void SetShader(std::string s_name) { this->shader = s_name.c_str(); }
	inline void SetTexture(std::string texture) { this->texture = texture.c_str(); }

	inline glm::vec3 getPosition() { return this->position; }
	inline glm::vec3 getRotation() { return this->rotation; }
	inline glm::vec3 getScale() { return this->scale; }

	inline void setPosition(glm::vec3 pos) { this->position = pos; this->model_matrix_changed = true; }
	inline void setRotation(glm::vec3 rot) { this->rotation = rot; this->model_matrix_changed = true;}
	inline void setScale(glm::vec3 scale) { this->scale = scale; this->model_matrix_changed = true;}

	void Translate(float x, float y, float z);
	void Translate(glm::vec3 trans);

	void RotateDegrees(float x, float y, float z);
	void RotateDegrees(glm::vec3 rot);

	void RotateRadians(float x, float y, float z);
	void RotateRadians(glm::vec3 rot);


	void Draw();
	void DrawInstanced();
	glm::mat4 GetModelMatrix();

private:
	bool model_matrix_changed;
	glm::mat4 model_matrix;

	void CheckRotations();

	inline void test() {}
};