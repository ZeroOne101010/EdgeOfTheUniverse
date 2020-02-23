#include "Mob.h"

Mob::Mob()
{
}


void Mob::draw(Renderer* renderer, Alterable alters)
{
	IntersectedEntity::draw(renderer, alters);
}

