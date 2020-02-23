#include "ItemConteiner.h"
#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::Inventory(RectangleShape* rect)
{
	ownerShape = rect;
}
