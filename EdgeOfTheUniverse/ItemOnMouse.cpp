#include "World.h"
#include"Map.h"
#include "Game.h"
#include "ItemOnMouse.h"

ItemOnMouse::ItemOnMouse(World* world)
{
	this->world = world;
	itemRect = new RectangleShape(38, 38);
	//itemRect->Color = vec4(0, 0, 0, 255);
}

ItemOnMouse::~ItemOnMouse()
{
	delete itemRect;
}

Alterable ItemOnMouse::draw(Renderer* renderer, Alterable alters)
{
	itemRect->Position = Cursor::getMousePosition(world->map->game->window->window) - vec2(itemRect->Size.x / 2, itemRect->Size.y / 2);
	renderer->draw(itemRect);
	return Alterable();
}
