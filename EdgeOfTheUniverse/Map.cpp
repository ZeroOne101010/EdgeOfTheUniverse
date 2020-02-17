#include "Game.h"
#include "Map.h"

Map::Map(Game* game)
{
	this->game = game;
	chunkThread = new ChunkThread();
	chunkThread->start();
	world = new World(0, this);
	world->Position = vec2(0, 0);
}

Map::~Map()
{
	chunkThread->close();
	delete chunkThread;
	delete world;
}

void Map::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	renderer->draw(world, alters);
}
