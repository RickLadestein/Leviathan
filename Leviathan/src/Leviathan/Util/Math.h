#pragma once
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/glm.hpp"

constexpr double PI = 3.14159265359;

constexpr float operator"" _deg(unsigned long long deg)
{
	return float(deg * (PI / 180));
}

constexpr float operator"" _deg(long double deg)
{
	return float(deg * (PI / 180));
}

inline glm::quat EulerAnglesToQuaternion(glm::vec3 angle_degrees) {
	glm::quat QuatAroundX = glm::angleAxis(glm::radians(angle_degrees.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat QuatAroundY = glm::angleAxis(glm::radians(angle_degrees.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat QuatAroundZ = glm::angleAxis(glm::radians(angle_degrees.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::quat finalOrientation = QuatAroundZ * QuatAroundY * QuatAroundX;
	return finalOrientation;
}

inline glm::quat EulerRadiansToQuaternion(glm::vec3 angle_radians) {
	glm::quat QuatAroundX = glm::angleAxis(angle_radians.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat QuatAroundY = glm::angleAxis(angle_radians.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat QuatAroundZ = glm::angleAxis(angle_radians.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::quat finalOrientation = QuatAroundZ * QuatAroundY * QuatAroundX;
	return finalOrientation;
}