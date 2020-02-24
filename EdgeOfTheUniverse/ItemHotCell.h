#pragma once
#include "Button.h"
#include "Panel.h"

class ItemHotCell : public Button
{
public:
	ItemHotCell();
	~ItemHotCell();
	
	Panel* item;
	bool drawItem = true;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

