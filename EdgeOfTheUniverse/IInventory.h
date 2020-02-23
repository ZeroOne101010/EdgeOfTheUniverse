#pragma once
#include <vector>
#include "Inventory.h"
#include "ITakeble.h"
class IInventory
{
public:
	std::vector<Inventory*> inventories;
	virtual void Take(ITakeble* target, int inventoryID) = 0;
};

