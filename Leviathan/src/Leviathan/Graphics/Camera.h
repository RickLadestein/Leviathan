#pragma once
#include "Leviathan/Core.h"
#include "glm/glm.hpp"
#include <memory>

enum class CameraMode {
	FREE,
	FPS
};

class Camera {
private:
	glm::vec3 position;
	glm::vec3 rotation;

	float near_plane, far_plane, aspect, fov;

	glm::mat4 projection_matrix;
	glm::mat4 inverse_projection_matrix;
	glm::mat4 view_matrix;
	glm::mat4 inverse_view_matrix;

	glm::vec3 camera_target;
	glm::vec3 camera_up;
	glm::vec3 camera_right;
	glm::vec3 camera_direction;

	bool update_needed;
	CameraMode mode;
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 rotation);
	void SetViewSettings(float fov, float width, float height, float Znear, float Zfar);
	void OnWindowSizeChanged(float width, float height);
	void GetViewSettings(float* fov, float* aspect, float* Znear, float* Zfar);

	inline glm::mat4 GetProjectionMatrix() { return this->projection_matrix; }
	inline glm::mat4 GetInverseProjectionMatrix() { return this->inverse_projection_matrix; }
	glm::mat4 GetViewMatrix();
	glm::mat4 GetInverseViewMatrix();
	glm::vec3 GetRightVector();
	glm::vec3 GetForewardVector();
	glm::vec3 GetUpVector();
	inline glm::vec3 GetRotation() { return this->rotation; }
	inline glm::vec3 GetPosition() { return this->position; }

	void Translate(glm::vec3 translation);
	void SetPosition(glm::vec3 pos);
	void Rotate(glm::vec3 rotation);

	void RotateX(float degrees);
	void RotateY(float degrees);
	void RotateZ(float degrees);

	static std::shared_ptr<Camera> GetPrimary();
private:
	void CalculateViewMatrix();
	void InitializeDefaults();
};