#pragma once
#include "AlterableHeader.h"
#include "Map.h"
#include "Slider.h"

class Game : public Alterable, public IDraw
{
public:
	Game(RenderWindow* window);
	~Game();

	RenderWindow* window;
	Map* map;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

