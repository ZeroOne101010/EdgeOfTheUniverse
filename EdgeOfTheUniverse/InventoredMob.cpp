#include "InventoredMob.h"

InventoredMob::InventoredMob()
{
}

void InventoredMob::Take(ITakeble* target, int inventoryID)
{
	target->Taked(this, &rect->Size, inventories[inventoryID]);
}

Alterable InventoredMob::draw(Renderer* renderer, Alterable alters)
{
	Mob::draw(renderer, alters);
	return alters;
}
