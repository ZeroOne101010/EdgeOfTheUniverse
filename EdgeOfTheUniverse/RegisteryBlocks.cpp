#include "World.h"
#include "RegisteryBlocks.h"

std::vector<Block*> RegisteryBlocks::block;
std::map<BlockName, int> RegisteryBlocks::nameMap;

void RegisteryBlocks::addBlock(Block* block, BlockName name)
{
	block->id = RegisteryBlocks::block.size();
	RegisteryBlocks::nameMap.insert(std::pair<BlockName, int>(name, block->id));
	RegisteryBlocks::block.push_back(block);
}

Block* RegisteryBlocks::createBlock(int pX, int pY, bool isBackBlock, World* world, int id)
{
	return RegisteryBlocks::block[id]->createBlock(pX, pY, isBackBlock, world);
}

Block* RegisteryBlocks::createBlock(int pX, int pY, bool isBackBlock, World* world, BlockName name)
{
	return RegisteryBlocks::block[RegisteryBlocks::nameMap[name]]->createBlock(pX, pY, isBackBlock, world);
}

void RegisteryBlocks::initBlocks()
{
	addBlock(new Air(), air);
	addBlock(new Vacuum(), vacuum);
	addBlock(new Dirt(), dirt);
	addBlock(new Grass(), grass);
	addBlock(new Stone(), stone);
}
