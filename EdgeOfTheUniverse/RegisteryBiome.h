#pragma once
#include <vector>

class Biome;

class RegisteryBiome
{
public:
	static std::vector<Biome*> biome;

	static void addBiome(Biome* biome);
	static Biome* createBiome(int id, World* world);
	static void init();
};

