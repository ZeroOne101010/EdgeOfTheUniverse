#pragma once
#include "Biome.h"
class Mountains : public Biome
{
public:
	Mountains(float limitUp, float limitDown);
	virtual Biome* getNewBiome() override;

};

