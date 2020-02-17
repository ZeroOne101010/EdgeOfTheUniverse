#include "Game.h"

Game::Game(RenderWindow* window)
{
	this->window = window;
	map = new Map(this);
}

Game::~Game()
{
	delete map;
}

void Game::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	renderer->draw(map, alters);
}