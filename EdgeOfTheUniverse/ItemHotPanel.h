#pragma once
#include "Panel.h"
#include "ItemHotCell.h"
#include "ButtonGroup.h"
class ItemHotPanel : public Panel
{
public:
	ItemHotPanel();
	~ItemHotPanel();
	
	static int coutItemInHotPanel;// Их количиство будет равно 10, тк для быстрого доступа доступно только 10 цифр
	ItemHotCell** itemSlot;

	ButtonGroup buttonGroup;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

