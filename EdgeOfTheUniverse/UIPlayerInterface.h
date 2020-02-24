#pragma once
#include "Panel.h"
#include "ItemHotPanel.h"
#include "InventoryItemsField.h"
#include "Inventory.h"
class World;
class Entity;

class UIPlayerInterface : public Panel
{
public:
	UIPlayerInterface(World* world, Controller* controller);
	~UIPlayerInterface();

	World* world;
	Controller* controller;
	ItemHotPanel* itemHotPanel;
	InventoryItemsField* inventoryItemsField;
	Inventory* inventory;


	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

