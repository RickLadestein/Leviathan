#pragma once
#include "Leviathan/Data/FastNoise.h"
#include "glm/glm.hpp"

class BaseTerrainGenerator {
protected:
	fnl_state noise;
	glm::vec3 offset;
	glm::vec3 scalar;
	float positive_multiplier;
	float negative_multiplier;
public:
	BaseTerrainGenerator() { 
		this->noise = fnlCreateState(); 
		offset = glm::vec3(0.0f);
		scalar = glm::vec3(0.0f);
		positive_multiplier = 1.0f;
		negative_multiplier = 1.0f;
	}
	~BaseTerrainGenerator() = default;

	float getNoiseLevel(glm::vec3& pos) {
		float x = (pos.x + offset.x) * scalar.x;
		float y = (pos.y + offset.y) * scalar.y;
		float z = (pos.z + offset.z) * scalar.z;

		float val = fnlGetNoise3D(&noise, x, y, z);
		if (val > 0.0f) {
			val *= positive_multiplier;
		}
		else {
			val *= negative_multiplier;
		}
		return val;
	}

	float getNoiseLevel(glm::vec2& pos) {
		float x = (pos.x + offset.x) * scalar.x;
		float y = (pos.y + offset.y) * scalar.y;

		float val = fnlGetNoise2D(&noise, x, y);
		if (val > 0.0f) {
			val *= positive_multiplier;
		}
		else {
			val *= negative_multiplier;
		}
		return val;
	}

	float getNoiseLevel(float x) {
		float _x = (x + offset.x) * scalar.x;

		float val = fnlGetNoise2D(&noise, _x, 0.0f);
		if (val > 0.0f) {
			val *= positive_multiplier;
		}
		else {
			val *= negative_multiplier;
		}
		return val;
	}

};