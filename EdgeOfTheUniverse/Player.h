#pragma once
#include "InventoredMob.h"
#include "Block.h"
class Player : public InventoredMob
{
public:
	Player();
	Inventory* mainInventory;
	virtual Entity* getNewEntity() override;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

