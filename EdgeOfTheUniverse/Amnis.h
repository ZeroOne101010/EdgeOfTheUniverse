#pragma once
#include "Item.h"
class Amnis : public Item
{
public:
	Amnis();
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;

	virtual Entity* getNewEntity() override;
};

