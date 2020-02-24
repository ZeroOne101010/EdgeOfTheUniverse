#include "Game.h"
#include "Map.h"
#include "Mountains.h"
#include "RockLayer.h"

Map::Map(int sizeNumberMap, int seed, Game* game)
{
	this->rand = new RandomCoor(seed, sizeNumberMap);
	this->game = game;
	chunkThread = new ChunkThread();
	chunkThread->start();
	world = new World(0, this);

	Mountains* mountains = new Mountains(4, 100);
	RockLayer* rockLayer = new RockLayer(6, 100);

	world->addBiome(mountains);
	world->addBiome(rockLayer);
	world->Position = vec2(0, 0);
	uiPlayerInterface = new UIPlayerInterface(world, world->controller);
}

Map::~Map()
{
	chunkThread->close();
	delete world;
	delete chunkThread;
	delete uiPlayerInterface;
}

Alterable Map::draw(Renderer* renderer, Alterable alters)
{
	alters *= this;
	renderer->draw(world, alters);
	//renderer->draw(testCon, alters);
	renderer->draw(uiPlayerInterface, alters);
	return alters;
}
