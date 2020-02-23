#include "InventoredMob.h"

void InventoredMob::Take(ITakeble* target, int id)
{
	target->Taked(&(Position + Origin), inventories[id]);
}
