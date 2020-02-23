#pragma once
#include "Mob.h"
#include "ITakeble.h"
class InventoredMob : public Mob
{
public:
	std::vector<Inventory*> inventories;
	void Take(ITakeble* target, int id);
};

