#include "Drawable.h"
#include <iostream>
#include <memory>
#include "Leviathan/Graphics/Shader.h"
#include "Leviathan/Graphics/Texture.h"
#include "glad/glad.h"

#include "Leviathan/Util/Math.h"

Drawable::Drawable()
{
	this->position = glm::vec3(0);
	this->rotation = glm::vec3(0);
	this->scale = glm::vec3(1);

	this->shader = "default";
	this->texture = "default";
	this->model_matrix_changed = true;
	this->model_matrix = glm::mat4(1.0f);
}

Drawable::Drawable(std::string shader, std::string texture)
{
	this->shader = shader.c_str();
	this->texture = texture.c_str();
	this->position = glm::vec3(0);
	this->rotation = glm::vec3(0);
	this->scale = glm::vec3(1);
	this->model_matrix_changed = true;
	this->model_matrix = glm::mat4(1.0f);
}

Drawable::Drawable(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->shader = "default";
	this->texture = "default";
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->model_matrix_changed = true;
	this->model_matrix = glm::mat4(1.0f);
}

Drawable::Drawable(std::string shader, std::string texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->shader = shader.c_str();
	this->texture = texture.c_str();
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->model_matrix_changed = true;
	this->model_matrix = glm::mat4(1.0f);
}



void Drawable::Translate(float x, float y, float z)
{
	this->position += glm::vec3(x, y, z);
	this->model_matrix_changed = true;
}

void Drawable::Translate(glm::vec3 trans)
{
	this->position += trans;
	this->model_matrix_changed = true;
}

void Drawable::RotateDegrees(float x, float y, float z)
{
	this->rotation += glm::vec3(x, y, z);
	this->CheckRotations();
	this->model_matrix_changed = true;

}

void Drawable::RotateDegrees(glm::vec3 rot)
{
	this->rotation += rot;
	this->CheckRotations();
	this->model_matrix_changed = true;
}

void Drawable::RotateRadians(float x, float y, float z)
{
	float rot_deg_x = glm::degrees(x);
	float rot_deg_y = glm::degrees(y);
	float rot_deg_z = glm::degrees(z);

	this->rotation += glm::vec3(rot_deg_x, rot_deg_y, rot_deg_z);
	this->CheckRotations();
	this->model_matrix_changed = true;
}

void Drawable::RotateRadians(glm::vec3 rot)
{
	float rot_deg_x = glm::degrees(rot.x);
	float rot_deg_y = glm::degrees(rot.y);
	float rot_deg_z = glm::degrees(rot.z);

	this->rotation += glm::vec3(rot_deg_x, rot_deg_y, rot_deg_z);
	this->CheckRotations();
	this->model_matrix_changed = true;
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
