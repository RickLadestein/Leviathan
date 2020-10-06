#pragma once
#include "Leviathan.h"
#include <vector>
class World {
	World() = default;
	~World() = default;
};

enum class WorldObjectType {
	SCENE,
	ENTITY
};