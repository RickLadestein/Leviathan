#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "Leviathan/Util/Math.h"

std::shared_ptr<Camera> primary;

Camera::Camera()
{
	this->InitializeDefaults();
}

Camera::Camera(glm::vec3 position, glm::vec3 rotation)
{
	this->InitializeDefaults();
	this->position = position;
	this->rotation = rotation;
}

void Camera::InitializeDefaults()
{
	this->aspect = 16.0f / 9.0f;
	this->camera_right = glm::vec3(0.0f);
	this->camera_target = glm::vec3(0.0f);
	this->camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->far_plane = 100.0f;
	this->near_plane = 0.001f;
	this->fov = glm::radians(45.0f);
	this->inverse_projection_matrix = glm::mat4(1.0f);
	this->inverse_view_matrix = glm::mat4(1.0f);
	this->view_matrix = glm::mat4(1.0f);
	this->projection_matrix = glm::mat4(1.0f);
	this->position = glm::vec3(0.0f, 0.0f, -1.0f);
	this->rotation = glm::vec3(0.0f);
	this->update_needed = true;
	this->mode = CameraMode::FPS;

	this->SetViewSettings(45, 1920, 1080, 0.001f, 1000.0f);
}


void Camera::SetViewSettings(float fov, float width, float height, float Znear, float Zfar)
{
	float ratio = width / height;
	this->fov = fov;
	this->near_plane = Znear;
	this->far_plane = Zfar;
	this->aspect = ratio;

	if (fov < 1.0f)
		fov = 1.0f;
	else if (fov > 179.0f)
		fov = 179.0f;

	this->projection_matrix = glm::perspective(fov, ratio, Znear, Zfar);
	this->inverse_projection_matrix = glm::inverse(this->projection_matrix);
}

void Camera::OnWindowSizeChanged(float width, float height)
{
	if (fov < 1.0f)
		fov = 1.0f;
	else if (fov > 179.0f)
		fov = 179.0f;

	this->projection_matrix = glm::perspective(fov, aspect, near_plane, far_plane);
	this->inverse_projection_matrix = glm::inverse(this->projection_matrix);
}

void Camera::GetViewSettings(float* fov, float* aspect, float* Znear, float* Zfar)
{
	*fov = this->fov;
	*aspect = this->aspect;
	*Znear = this->near_plane;
	*Zfar = this->far_plane;
}

glm::mat4 Camera::GetViewMatrix()
{
	this->CalculateViewMatrix();
	return this->view_matrix;
}

glm::mat4 Camera::GetInverseViewMatrix()
{
	this->CalculateViewMatrix();
	return this->inverse_view_matrix;
}

glm::vec3 Camera::GetRightVector()
{
	this->CalculateViewMatrix();
	return this->camera_right;
}

glm::vec3 Camera::GetForewardVector()
{
	if(this->update_needed)
		this->CalculateViewMatrix();
	return this->camera_target - this->position;
}

glm::vec3 Camera::GetUpVector()
{
	if (this->mode == CameraMode::FPS) {
		return glm::vec3(0.0f, 1.0f, 0.0f);
	}
	else {
		return this->camera_up;
	}
}

void Camera::Translate(glm::vec3 translation)
{
	this->position += translation;
	this->update_needed = true;
}

void Camera::SetPosition(glm::vec3 pos)
{
	this->position = pos;
	this->update_needed = true;
}

void Camera::Rotate(glm::vec3 rotation)
{
	this->RotateX(rotation.x);
	this->RotateY(rotation.y);
	this->RotateZ(rotation.z);
	this->CalculateViewMatrix();
	
}

void Camera::RotateX(float degrees)
{
	if (this->mode == CameraMode::FPS) {
		this->rotation.x -= degrees;
		if (this->rotation.x > 89.0f)
			this->rotation.x = 89.0f;
		else if (this->rotation.x < -89.0f)
			this->rotation.x = -89.0f;
	}
	else {
		this->rotation.x -= degrees;
		if (this->rotation.x > 360.0f)
			this->rotation.x = (this->rotation.x - 360.0f);
		else if (this->rotation.x < 0.0f)
			this->rotation.x = 360.0f - this->rotation.x;
	}
	this->update_needed = true;
}

void Camera::RotateY(float degrees)
{
	this->rotation.y -= degrees;
	if (this->rotation.y > 360.0f)
		this->rotation.y = (this->rotation.y - 360.0f);
	else if (this->rotation.y < 0.0f)
		this->rotation.y = 360.0f - this->rotation.y;
	this->update_needed = true;
}

void Camera::RotateZ(float degrees)
{
	this->rotation.z -= degrees;
	if (this->rotation.z > 360.0f)
		this->rotation.z = (this->rotation.z - 360.0f);
	else if (this->rotation.z < 0.0f)
		this->rotation.z = 360.0f - this->rotation.z;
	this->update_needed = true;
}

std::shared_ptr<Camera> Camera::GetPrimary()
{
	if (primary == nullptr) {
		primary = std::make_shared<Camera>();
	}
	return primary;
}

void Camera::CalculateViewMatrix()
{
		glm::quat QuatAroundX = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
		glm::quat QuatAroundY = glm::quat(glm::vec3(0.0f, glm::radians(this->rotation.y), 0.0f));
		glm::quat QuatAroundZ = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(-this->rotation.x)));
		glm::quat finalOrientation = QuatAroundX * QuatAroundY * QuatAroundZ;
		glm::vec3 point(1.0f, 0.0f, 0.0f);
		this->camera_target = (finalOrientation * point) + this->position;

		this->camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->camera_direction = glm::normalize(this->position - this->camera_target);
		this->camera_right = glm::normalize(glm::cross(this->camera_up, this->camera_direction));
		this->camera_up = glm::normalize(glm::cross(this->camera_direction, this->camera_right));

	if (this->update_needed) {
		this->view_matrix = glm::lookAt(this->position, this->camera_target, this->camera_up);
	}
	return;
}

