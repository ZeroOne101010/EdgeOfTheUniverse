#pragma once
#include "AlterableHeader.h"
#include "Map.h"
class Game : public Alterable, public IDraw
{
public:
	Game(RenderWindow* window);
	~Game();

	RenderWindow* window;
	Map* map;

	virtual void draw(Renderer* renderer, Alterable alters) override;
};
