#include "World.h"
#include "Entity.h"
#include "UIPlayerInterface.h"

//В будущем нужно использовать инвентарь игрока, хотя вернее нужно даже не игрока в конструкторе получать, а IInventory или что то типо того

UIPlayerInterface::UIPlayerInterface(World* world, Entity* player)
{
	Color = glm::vec4(20, 20, 20, 255);
	Color = vec4(0, 0, 0, 0);
	this->world = world;
	this->player = player;
	size = vec2(0, 0);

	itemHotPanel = new ItemHotPanel();
	itemHotPanel->buttonAttached = true;;
	itemHotPanel->Color = vec4(20, 20, 20, 255);

	inventoryItemsField = new InventoryItemsField();	
	inventoryItemsField->buttonAttached = true;
	inventoryItemsField->Position = vec2(0, itemHotPanel->size.y + 10);
}

UIPlayerInterface::~UIPlayerInterface()
{
	delete itemHotPanel;
	delete inventoryItemsField;
}

Alterable UIPlayerInterface::draw(Renderer* renderer, Alterable alters)
{
	Panel::draw(renderer, alters);
	renderer->draw(itemHotPanel, alters);
	renderer->draw(inventoryItemsField, alters);
	return alters;
}
