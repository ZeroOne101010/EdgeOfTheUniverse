#include "Game.h"
Game::Game(RenderWindow* window)
{
	this->window = window;
	map = new Map(1000, 345, this);
}

Game::~Game()
{
	delete map;
}

Alterable Game::draw(Renderer* renderer, Alterable alters)
{
	alters *= this;
	renderer->draw(map, alters);
	return alters;
}
