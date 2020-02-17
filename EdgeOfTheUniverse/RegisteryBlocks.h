#pragma once
#include <iostream>
#include <vector>

#include "Air.h"
#include "Vacuum.h"
#include "Dirt.h"

class World;

class RegisteryBlocks
{
public:
	static std::vector<Block*> block;

	static void addBlock(Block* block);
	static Block* createBlock(int pX, int pY, bool isBackBlock, World* world, int id);

	static void initBlocks();

};

