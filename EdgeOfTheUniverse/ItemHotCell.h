#pragma once
#include "Button.h"
#include "Panel.h"

class ItemHotCell : public Button
{
public:
	ItemHotCell();
	~ItemHotCell();

	Panel* item;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

