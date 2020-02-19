#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "Air.h"
#include "Vacuum.h"
#include "Dirt.h"
#include "Grass.h"

class World;

enum BlockName
{
	NA,
	air,
	vacuum,
	dirt,
	grass
};

class RegisteryBlocks
{
public:

	static std::vector<Block*> block;
	static std::map<BlockName, int> nameMap;

	static void addBlock(Block* block, BlockName name);
	static Block* createBlock(int pX, int pY, bool isBackBlock, World* world, int id);
	static Block* createBlock(int pX, int pY, bool isBackBlock, World* world, BlockName name);

	static void initBlocks();

};

