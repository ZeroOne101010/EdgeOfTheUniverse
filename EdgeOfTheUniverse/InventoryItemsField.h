#pragma once
#include "Button.h"
#include "Panel.h"
#include "ItemHotCell.h"
#include "ButtonGroup.h"

class InventoryItemsField : public Panel
{
public:

	InventoryItemsField();
	~InventoryItemsField();

	ItemHotCell* getItemContainer(int id);
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;

	int countItemsX = 10;
	int countItemsY = 10;

	ItemHotCell*** itemCell;
	ButtonGroup buttonGroup;
};

