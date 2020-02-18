#include "Biome.h"
#include "RegisteryBiome.h"

std::vector<Biome*> RegisteryBiome::biome;

void RegisteryBiome::addBiome(Biome* biome)
{
	biome->id = RegisteryBiome::biome.size();
	RegisteryBiome::biome.push_back(biome);
}

Biome* RegisteryBiome::createBiome(int id, World* world)
{
	Biome* biome = RegisteryBiome::biome[id]->createBiome(world);
	return biome;
}

void RegisteryBiome::init()
{

}
