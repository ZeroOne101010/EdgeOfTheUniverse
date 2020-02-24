#pragma once
#include "AlterableHeader.h"
#include "Vacuum.h"

class World;

class Chunk
{
public:
	Chunk(World* world, int chunkX, int chunkY);
	~Chunk();

	void deleteBlocks();

	static const int sizeChunk;

	int chunkX = 0;
	int chunkY = 0;

	int biome1 = NULL;
	int biome2 = NULL;
	int biome2Info = NULL;

	World* world;

	Block*** block;
	Block*** backBlock;

	void updateCloseBlocks();
};

