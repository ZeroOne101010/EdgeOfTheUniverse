#include "World.h"
#include "Entity.h"
#include "UIPlayerInterface.h"

//В будущем нужно использовать инвентарь игрока, хотя вернее нужно даже не игрока в конструкторе получать, а IInventory или что то типо того

UIPlayerInterface::UIPlayerInterface(World* world, Entity* player)
{
	Color = glm::vec4(20, 20, 20, 255);
	buttonAttached = true;
	Color = vec4(0, 0, 0, 0);
	this->world = world;
	this->player = player;
	size = vec2(0, 0);

	itemHotPanel = new ItemHotPanel();
	itemHotPanel->Color = vec4(20, 20, 20, 255);
	itemHotPanel->size = vec2(700, 60);
	itemHotPanel->pos = vec2(0, -60);
}

UIPlayerInterface::~UIPlayerInterface()
{
	delete itemHotPanel;
}

Alterable UIPlayerInterface::draw(Renderer* renderer, Alterable alters)
{
	alters = Panel::draw(renderer, alters);
	renderer->draw(itemHotPanel, alters);
	return alters;
}
