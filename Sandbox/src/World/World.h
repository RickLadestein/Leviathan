#pragma once
#include "Leviathan.h"
#include "Chunk.h"
#include "Player.h"
#include <vector>
#include <memory>

typedef std::weak_ptr<Player> WeakPlayerReference;

class World {
	World() = default;
	~World() = default;

	WeakPlayerReference Player;

	std::shared_ptr<Chunk> chunks[25][25];

private:

};