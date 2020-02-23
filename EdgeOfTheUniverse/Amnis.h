#pragma once
#include "Item.h"
class Amnis : public Item
{
public:
	Amnis();
	virtual void draw(Renderer* renderer, Alterable alters) override;

	virtual Entity* getNewEntity() override;
};

