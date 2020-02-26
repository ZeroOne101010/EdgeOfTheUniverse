#pragma once
#include "Button.h"
#include "Panel.h"
#include "EventTakeItemCell.h"

class ItemHotPanel;

class ItemHotCell : public Button
{
public:
	ItemHotCell();
	~ItemHotCell();
	
	Panel* item;
	bool drawItem = false;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

