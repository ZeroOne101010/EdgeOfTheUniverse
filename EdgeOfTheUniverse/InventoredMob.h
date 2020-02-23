#pragma once
#include "Mob.h"
#include "IInventory.h"
class InventoredMob : public Mob, public IInventory
{
public:
	InventoredMob();

	virtual void Take(ITakeble* target, int inventoryID) override;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

