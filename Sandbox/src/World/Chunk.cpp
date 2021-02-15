#include "Chunk.h"

void Block::setNeighbours(bool up, bool down, bool front, bool back, bool left, bool right)
{
	uint8_t val = 0;
	if (up) {
		val |= 1 << 7;
	}

	if (down) {
		val |= 1 << 6;
	}

	if (front) {
		val |= 1 << 5;
	}

	if (back) {
		val |= 1 << 4;
	}

	if (left) {
		val |= 1 << 3;
	}

	if (right) {
		val |= 1 << 2;
	}
	this->neighbours = val;
}



Chunk::Chunk(glm::vec2 chunk_start)
{
}

Block* Chunk::GetBlock(size_t x, size_t y, size_t z)
{
	return nullptr;
}

void Chunk::SetBlock(Block& block, size_t x, size_t y, size_t z)
{
}
