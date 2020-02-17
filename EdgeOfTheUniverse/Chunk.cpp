#include "World.h"
#include "RegisteryBlocks.h"
#include "ICloseObject.h"
#include "Chunk.h"

const int Chunk::sizeChunk = 30;

Chunk::Chunk(World* world, int chunkX, int chunkY)
{
	this->world = world;
	this->chunkX = chunkX;
	this->chunkY = chunkY;

	block = new Block**[sizeChunk];
	backBlock = new Block**[sizeChunk];

	for (int x = 0; x < sizeChunk; x++)
	{
		block[x] = new Block * [sizeChunk];
		backBlock[x] = new Block * [sizeChunk];
	}

	for(int x = 0; x < sizeChunk; x++)
		for (int y = 0; y < sizeChunk; y++)
		{
			block[x][y] = RegisteryBlocks::createBlock(chunkX * sizeChunk + x, chunkY * sizeChunk + y, false, world, 1);
			backBlock[x][y] = RegisteryBlocks::createBlock(chunkX * sizeChunk + x, chunkY * sizeChunk + y, false, world, 2);
		}

	for (int x = 10; x < 15; x++)
	{
		block[x][5] = RegisteryBlocks::createBlock(chunkX * sizeChunk + x, chunkY * sizeChunk + 5, false, world, 2);
	}
}

Chunk::~Chunk()
{
	for (int x = 0; x < sizeChunk; x++)
		for (int y = 0; y < sizeChunk; y++)
		{
			if (block[x][y] != nullptr) delete block[x][y];
			if (backBlock[x][y] != nullptr) delete backBlock[x][y];
		}
}

void Chunk::updateCloseBlocks()
{
	for (int x = 0; x < sizeChunk; x++)
		for (int y = 0; y < sizeChunk; y++)
		{
			ICloseObject* closeObject = dynamic_cast<ICloseObject*>(block[x][y]);
			if (closeObject != nullptr)
			{
				closeObject->updateObject();
			}
		}

	for (int x = 0; x < sizeChunk; x++)
		for (int y = 0; y < sizeChunk; y++)
		{
			ICloseObject* closeObject = dynamic_cast<ICloseObject*>(backBlock[x][y]);
			if (closeObject != nullptr)
			{
				closeObject->updateObject();
			}
		}
}