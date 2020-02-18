#include "BiomeAir.h"

BiomeAir::BiomeAir() : Biome(Chunk::sizeChunk, Chunk::sizeChunk, 234, 12, 0.5f, 0.5f, 2, 2, -10000000, 10000000)
{
	addSpawnBlock(RegisteryBlocks::block[0], 10, 10, 123, 453, 1, -2, 1);
}

Biome* BiomeAir::getNewBiome()
{
	return nullptr;
}
