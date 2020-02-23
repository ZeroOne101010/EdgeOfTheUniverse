#include "InventoredEntity.h"


void InventoredEntity::Take(ITakeble* target, int id)
{
	target->Taked(&(Position + Origin), inventories[id]);
}
