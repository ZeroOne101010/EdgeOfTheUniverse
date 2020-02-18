#pragma once
#include "Biome.h"
class BiomeAir : public Biome
{
public:
	BiomeAir();
	virtual Biome* getNewBiome() override;
};

