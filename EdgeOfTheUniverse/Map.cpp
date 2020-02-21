#include "Game.h"
#include "Map.h"
#include "Mountains.h"

Map::Map(int sizeNumberMap, int seed, Game* game)
{
	this->rand = new RandomCoor(seed, sizeNumberMap);
	this->game = game;
	chunkThread = new ChunkThread();
	chunkThread->start();
	world = new World(0, this);

	Mountains* mountains = new Mountains(4, 100);

	world->addBiome(mountains);
	world->Position = vec2(0, 0);
}

Map::~Map()
{
	chunkThread->close();
	delete world;
	delete chunkThread;
}

void Map::draw(Renderer* renderer, Alterable alters)
{
	alters *= this;
	renderer->draw(world, alters);
}
