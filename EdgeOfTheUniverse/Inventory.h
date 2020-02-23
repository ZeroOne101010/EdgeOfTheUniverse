#pragma once
#include <vector>
#include "ItemConteiner.h"
class Inventory
{
public:
	Inventory(int maxSlots);
	int maxSlots;
	std::vector<ItemConteiner> slots;
	bool full;
};

