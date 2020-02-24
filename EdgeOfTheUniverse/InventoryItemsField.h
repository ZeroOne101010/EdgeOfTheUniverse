#pragma once
#include "Button.h"
#include "Panel.h"
#include "ItemHotCell.h"
#include "ButtonGroup.h"
#include "Controller.h"
class InventoryItemsField : public Panel
{
public:

	InventoryItemsField(Controller* controller, int* coutItemInHotPanel);
	~InventoryItemsField();

	ItemHotCell* getItemContainer(int id);
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
	Controller* controller;
	int countItemsX = 10;
	int countItemsY = 5;
	int* coutItemInHotPanel;

	ItemHotCell*** itemCell;
	ButtonGroup buttonGroup;
private:
	void UpdateCells();
	void UpdteKeepedCell();
};

