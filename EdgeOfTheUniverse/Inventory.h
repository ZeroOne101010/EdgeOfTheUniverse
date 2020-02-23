#pragma once
#include <vector>
class ItemConteiner;
class Inventory
{
public:
	Inventory();
	Inventory(RectangleShape* rect);
	int maxSlots = 20;
	int fullSlots;
	std::vector<ItemConteiner> inventoryItems;
	RectangleShape* ownerShape;
	bool inventoryFull;
};

