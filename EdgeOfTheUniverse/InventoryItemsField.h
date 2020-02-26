#pragma once
#include "Button.h"
#include "Panel.h"
#include "ItemHotCell.h"
#include "ButtonGroup.h"
#include "Controller.h"
class InventoryItemsField : public Panel
{
public:

	InventoryItemsField(World* world, Controller* controller, int* coutItemInHotPanel);
	~InventoryItemsField();

	ItemHotCell* getItemContainer(int id);
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
	Controller* controller;
	World* world;
	int countItemsX = 10;
	int countItemsY = 5;
	int* coutItemInHotPanel;

	ItemHotCell*** itemCell;
	ButtonGroup buttonGroup;
private:
	void UpdateCells();
};

