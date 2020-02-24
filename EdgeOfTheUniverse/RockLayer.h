#pragma once
#include "Biome.h"
class RockLayer : public Biome
{
public:
	RockLayer(float limitUp, float limitDown);

	virtual Biome* getNewBiome() override;
};

