#include "Mountains.h"

Mountains::Mountains(float limitUp, float limitDown) : Biome(Chunk::sizeChunk, Chunk::sizeChunk, 1234, 12345, 1, 1, 1, 0.1f, -1000, 1000)
{
	addSpawnBlock(RegisteryBlocks::block[2], 10, 10, 123, 345, 1, 0, 2);
}

Biome* Mountains::getNewBiome()
{
	return nullptr;
}
