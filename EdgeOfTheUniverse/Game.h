#pragma once
#include "AlterableHeader.h"
#include "Map.h"
#include "Slider.h"

class Game : public Alterable, public IDraw
{
public:
	Game(RenderWindow* window);
	~Game();

	Slider* slider;

	RenderWindow* window;
	Map* map;

	virtual void draw(Renderer* renderer, Alterable alters) override;
};

