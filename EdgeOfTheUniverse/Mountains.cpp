#include "Mountains.h"

Mountains::Mountains(float limitUp, float limitDown) : Biome(20, 20, 34234, 4532, 1, 1, 1, -10, -10000, 10000)
{
	setLandshaft(Chunk::sizeChunk, Chunk::sizeChunk, 234234, 3456, 1, 1, 10);
	addSpawnBlock(RegisteryBlocks::block[2], 20, 20, 34534, 345, 1, 0.2f, 1);
	addSpawnBlock(RegisteryBlocks::block[4], 20, 20, 34534, 345, 1, 0.2f, 20, 10000, 1);
}

void Mountains::editChunk(Chunk* chunk, Block*** block, Block*** backBlock, int sizeBlockX, int sizeBlockY)
{
	EditChunkHelper::setGrass(chunk, block, backBlock, 3, 2, sizeBlockX, sizeBlockY);
}

Biome* Mountains::getNewBiome()
{
	return nullptr;
}
