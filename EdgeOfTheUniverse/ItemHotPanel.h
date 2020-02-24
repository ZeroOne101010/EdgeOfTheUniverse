#pragma once
#include "Panel.h"
#include "ItemHotCell.h"
#include "ButtonGroup.h"
#include "Controller.h"
#include "IInventory.h"
#include "RegisteryEntity.h"
class ItemHotPanel : public Panel
{
public:
	ItemHotPanel(Controller* controller);
	~ItemHotPanel();
	
	static int coutItemInHotPanel;// Их количиство будет равно 10, тк для быстрого доступа доступно только 10 цифр
	ItemHotCell** itemSlot;
	Controller* controller;
	ButtonGroup buttonGroup;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
private:
	void UpdateCells();
};

