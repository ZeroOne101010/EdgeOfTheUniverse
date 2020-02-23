#pragma once
#include "AlterableHeader.h"
#include "World.h"
#include "ChunkThread.h"
#include "RandomCoor.h"
#include "UIPlayerInterface.h"
#include "TestConteiner.h"
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

	UIPlayerInterface* uiPlayerInterface;

	TestConteiner* testCon;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

