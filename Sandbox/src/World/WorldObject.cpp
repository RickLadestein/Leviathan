#include "WorldObject.h"

void WorldObject::Translate(glm::vec3& translation)
{
	this->setPosition(this->position + translation);
}

void WorldObject::Translate(float x, float y, float z)
{
	glm::vec3 trans(x, y, z);
	this->Translate(trans);
}

void WorldObject::RotateDeg(glm::vec3& rotation)
{
	this->setRotation(this->rotation + rotation);
}

void WorldObject::RotateDeg(float x_rot, float y_rot, float z_rot)
{
	glm::vec3 rot(x_rot, y_rot, z_rot);
	this->RotateDeg(rot);
}

void WorldObject::RotateRad(glm::vec3& rotation)
{
	float rot_deg_x = glm::degrees(rotation.x);
	float rot_deg_y = glm::degrees(rotation.y);
	float rot_deg_z = glm::degrees(rotation.z);
	glm::vec3 rot(rot_deg_x, rot_deg_y, rot_deg_z);
	this->RotateDeg(rot);
}

void WorldObject::RotateRad(float x_rot, float y_rot, float z_rot)
{
	float rot_deg_x = glm::degrees(x_rot);
	float rot_deg_y = glm::degrees(y_rot);
	float rot_deg_z = glm::degrees(z_rot);
	glm::vec3 rot(rot_deg_x, rot_deg_y, rot_deg_z);
	this->RotateDeg(rot);
}

void WorldObject::Scale(glm::vec3& scalar)
{
	this->setScale(this->scale * scalar);
}

void WorldObject::Scale(float x_scl, float y_scl, float z_scl)
{
	glm::vec3 scl(x_scl, y_scl, z_scl);
	this->Scale(scl);
}
