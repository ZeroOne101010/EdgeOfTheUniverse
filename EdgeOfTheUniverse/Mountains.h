#pragma once
#include "Biome.h"
#include "EditChunkHelper.h"
class Mountains : public Biome
{
public:
	Mountains(float limitUp, float limitDown);
	void editChunk(Chunk* chunk, Block*** block, Block*** backBlock, int sizeBlockX, int sizeBlockY) override;
	virtual Biome* getNewBiome() override;

};

