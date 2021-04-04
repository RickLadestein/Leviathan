#pragma once
#include "Leviathan/Graphics/Drawable.h"
#include "Leviathan/Data/Entity.h"
class WorldObject : public Leviathan::Graphics::Drawable, public Entity {
public:
	WorldObject() : Leviathan::Graphics::Drawable(), Entity() {
		this->scale = glm::vec3(1.0f);
		this->position = glm::vec3(0.0f);
		this->rotation = glm::vec3(0.0f);
	}

	~WorldObject() = default;

	/// <summary>
	/// Translates the Entity from current position
	/// </summary>
	/// <param name="translation">translation vector (x,y,z)</param>
	void Translate(glm::vec3& translation);

	/// <summary>
	/// Translates the Entity from current position
	/// </summary>
	/// <param name="x">Translation x component</param>
	/// <param name="y">Translation y component</param>
	/// <param name="z">Translation z component</param>
	void Translate(float x, float y, float z);

	/// <summary>
	/// Rotates the Entity in degrees
	/// </summary>
	/// <param name="rotation">degrees rotation vector (x,y,z)</param>
	void RotateDeg(glm::vec3& rotation);

	/// <summary>
	/// Rotates the Entity in degrees
	/// </summary>
	/// <param name="x_rot">Rotation x component</param>
	/// <param name="y_rot">Rotation y component</param>
	/// <param name="z_rot">Rotation z component</param>
	void RotateDeg(float x_rot, float y_rot, float z_rot);


	/// <summary>
	/// Rotates the Entity in radians
	/// </summary>
	/// <param name="rotation">radians rotation vector (x,y,z)</param>
	void RotateRad(glm::vec3& rotation);

	/// <summary>
	/// Rotates the Entity in radians
	/// </summary>
	/// <param name="x_rot">Rotation x component</param>
	/// <param name="y_rot">Rotation y component</param>
	/// <param name="z_rot">Rotation z component</param>
	void RotateRad(float x_rot, float y_rot, float z_rot);

	/// <summary>
	/// Scales the Entity
	/// </summary>
	/// <param name="scalar">scalar vector (x,y,z)</param>
	void Scale(glm::vec3& scalar);

	/// <summary>
	/// Scales the Entity
	/// </summary>
	/// <param name="x_scl">Scalar x component</param>
	/// <param name="y_scl">Scalar x component</param>
	/// <param name="z_scl">Scalar x component</param>
	void Scale(float x_scl, float y_scl, float z_scl);
};