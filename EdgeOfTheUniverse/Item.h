#pragma once
#include "IntersectedEntity.h"
#include "ITakeble.h"
class Item : public IntersectedEntity, public ITakeble
{
public:
	Item();
	virtual void Take() override;
	int itemID;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

