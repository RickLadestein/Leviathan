#pragma once
#include "BaseTerrainGenerator.h"

class TerrainGenerator : public BaseTerrainGenerator {
public:
	TerrainGenerator() {
		noise.noise_type = FNL_NOISE_PERLIN;
		noise.octaves = 8;
		positive_multiplier = 1;
		negative_multiplier = 1;
		scalar = glm::vec3(0.15f);
	}
	~TerrainGenerator() = default;
};