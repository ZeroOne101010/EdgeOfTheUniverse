#pragma once
#include "AlterableHeader.h"
#include "World.h"
#include "ChunkThread.h"
#include "RandomCoor.h"

class Game;

class Map : public Alterable, public IDraw
{
public:
	Map(int sizeChumberMap, int seed, Game* game);
	~Map();

	World* world;
	ChunkThread* chunkThread;
	Game* game;
	RandomCoor* rand;

	virtual void draw(Renderer* renderer, Alterable alters) override;
};

