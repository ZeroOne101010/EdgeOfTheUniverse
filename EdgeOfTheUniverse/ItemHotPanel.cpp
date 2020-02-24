#include "ItemHotPanel.h"

int ItemHotPanel::coutItemInHotPanel = 10;

ItemHotPanel::ItemHotPanel(Controller* controller, World* world, UIPlayerInterface* playerInterface)
{
	this->playerInterface = playerInterface;
	this->world = world;
	this->controller = controller;
	itemSlot = new ItemHotCell * [coutItemInHotPanel];
	int offset = 5;
	for (int x = 0; x < coutItemInHotPanel; x++)
	{
		itemSlot[x] = new ItemHotCell();
		buttonGroup.Add(itemSlot[x]);
		itemSlot[x]->Position = vec2(x * (itemSlot[x]->size.x + offset) + offset, offset);
	}
	size = vec2((itemSlot[0]->size.x + offset) * coutItemInHotPanel + offset, itemSlot[0]->size.y + offset * 2);
	itemOnMouse = new ItemOnMouse(world);
}

ItemHotPanel::~ItemHotPanel()
{
	delete[coutItemInHotPanel] itemSlot;
	delete itemOnMouse;
}

void ItemHotPanel::UpdateCells()
{
	if (dynamic_cast<IInventory*>(controller->target))
	{
		for (int x = 0; x < dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots.size()& x < coutItemInHotPanel; x++)
		{

			int ID = dynamic_cast<IInventory*>(controller->target)->inventories[0]->slots[x].id;
			itemSlot[x]->item->carcass->tbo = RegisteryEntity::entity[ID]->rect->tbo;
			itemSlot[x]->item->carcass->textureRect = RegisteryEntity::entity[ID]->textureRect;
			itemSlot[x]->item->Color = vec4(255, 255, 255, 255);
		}
	}

}

Alterable ItemHotPanel::draw(Renderer* renderer, Alterable alters)
{
	alters = Panel::draw(renderer, alters);
	UpdateCells();
	for (int x = 0; x < coutItemInHotPanel; x++)
	{
		renderer->draw(itemSlot[x], alters);
	}
	renderer->draw(itemOnMouse, alters);
	return alters;
}


