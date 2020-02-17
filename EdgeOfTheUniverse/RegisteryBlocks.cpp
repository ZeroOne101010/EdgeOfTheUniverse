#include "World.h"
#include "RegisteryBlocks.h"

std::vector<Block*> RegisteryBlocks::block;

void RegisteryBlocks::addBlock(Block* block)
{
	block->id = RegisteryBlocks::block.size();
	RegisteryBlocks::block.push_back(block);
}

Block* RegisteryBlocks::createBlock(int pX, int pY, bool isBackBlock, World* world, int id)
{
	return RegisteryBlocks::block[id]->createBlock(pX, pY, isBackBlock, world);
}

void RegisteryBlocks::initBlocks()
{
	addBlock(new Air());
	addBlock(new Vacuum());
	addBlock(new Dirt());
}
