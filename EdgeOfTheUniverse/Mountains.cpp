#include "Mountains.h"

Mountains::Mountains(float limitUp, float limitDown) : Biome(20, 20, 34234, 4532, 1, 1, 1, -10, 0, 50)
{
	setLandshaft(Chunk::sizeChunk, Chunk::sizeChunk, 1, 1, 10, 1);
	addSpawnBlock(RegisteryBlocks::block[2], 20, 20, 0, 0, 1, -10, 1);
}

void Mountains::editChunk(Chunk* chunk, Block*** block, Block*** backBlock, int sizeBlockX, int sizeBlockY)
{
	EditChunkHelper::setGrass(chunk, block, backBlock, 3, sizeBlockX, sizeBlockY);
}

Biome* Mountains::getNewBiome()
{
	return nullptr;
}
