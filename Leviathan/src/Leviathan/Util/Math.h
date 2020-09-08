#pragma once
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/glm.hpp"
inline glm::quat EulerAnglesToQuaternion(glm::vec3 angle_degrees) {
	glm::quat QuatAroundX = glm::quat(glm::vec3(glm::radians(angle_degrees.x), 0.0f, 0.0f));
	glm::quat QuatAroundY = glm::quat(glm::vec3(0.0f, glm::radians(angle_degrees.y), 0.0f));
	glm::quat QuatAroundZ = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(angle_degrees.z)));
	glm::quat finalOrientation = QuatAroundX * QuatAroundY * QuatAroundZ;
	return finalOrientation;
}

inline glm::quat EulerRadiansToQuaternion(glm::vec3 angle_radians) {
	glm::quat QuatAroundX = glm::quat(glm::vec3(angle_radians.x, 0.0f, 0.0f));
	glm::quat QuatAroundY = glm::quat(glm::vec3(0.0f, angle_radians.y, 0.0f));
	glm::quat QuatAroundZ = glm::quat(glm::vec3(0.0f, 0.0f, angle_radians.z));
	glm::quat finalOrientation = QuatAroundX * QuatAroundY * QuatAroundZ;
	return finalOrientation;
}