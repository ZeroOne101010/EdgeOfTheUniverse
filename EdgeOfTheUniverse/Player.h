#pragma once
#include "Block.h"
#include "InventoredMob.h"
class Player : public InventoredMob
{
public:
	Player();
	Inventory* mainInventory;
	virtual Entity* getNewEntity() override;
};

