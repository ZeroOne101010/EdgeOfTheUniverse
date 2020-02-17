#pragma once
#include "AlterableHeader.h"
#include "World.h"
#include "ChunkThread.h"

class Game;

class Map : public Alterable, public IDraw
{
public:
	Map(Game* game);
	~Map();

	World* world;
	ChunkThread* chunkThread;
	Game* game;

	virtual void draw(Renderer* renderer, Alterable alters) override;
};

