#pragma once
#include "IntersectedEntity.h"
#include "ITakeble.h"
class Item : public IntersectedEntity, public ITakeble
{
public:
	Item();
	virtual void Take() override;
	int itemID;
	virtual void draw(Renderer* renderer, Alterable alters) override;
};

