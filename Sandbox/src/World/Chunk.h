#pragma once
#include <inttypes.h>
#include "glm/glm.hpp"
#include "Leviathan/Graphics/Drawable.h"
#include "Leviathan/Data/Entity.h"

#include "TerrainGenerators/TerrainGenerator.h"
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 256
#define CHUNK_WATER_START 62

#define MAX_LIGHT_LEVEL 256

using Leviathan::Graphics::Drawable;

enum class BlockFace {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

class Block {
public:
	union {
		struct {
			/// <summary>
			/// block identifier number (0-4.294.967.296)
			/// </summary>
			uint32_t block_id;

			/// <summary>
			/// bitshifted block neighbours (0-255) (TOP-BOTTOM-FRONT-BACK-LEFT-RIGHT-NUSE-NUSE)
			/// </summary>
			uint8_t neighbours;

			/// <summary>
			/// light emission factor (0-255)
			/// </summary>
			uint8_t emission_factor;

			/// <summary>
			/// transparency (0-255)
			/// </summary>
			uint8_t transperantcy;

			/// <summary>
			/// block break progress (0-255)
			/// </summary>
			uint8_t break_progress;
		};
		uint64_t data;
	};

	inline void setId(uint32_t id)						{ this->block_id = id; }
	inline void setLightFactor(uint8_t light_factor)	{ this->emission_factor = light_factor; }
	inline void setTransparentcy(uint8_t transp)		{ this->transperantcy = transp; }
	inline void setNeighbours(uint8_t neighbours)		{ this->neighbours = neighbours; }
	inline void setBreakProgress(uint8_t progress)		{ this->break_progress = progress;}

	void setNeighbours(bool up, bool down, bool front, bool back, bool left, bool right);
};

class Chunk : public Drawable, Entity {
private:
	TerrainGenerator tgen;
	Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];
public:
	Chunk(glm::vec2 chunk_start);
	~Chunk() = default;

	//Chunk(Chunk const& other) = delete;
	//Chunk(Chunk&& other) = delete;
	//Chunk operator=(Chunk const& other) = delete;
	//Chunk& operator=(Chunk&& other) = delete;


	Block* GetBlock(size_t x, size_t y, size_t z);
	void SetBlock(Block& block, size_t x, size_t y, size_t z);
};