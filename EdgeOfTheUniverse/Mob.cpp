#include "Mob.h"

float Mob::G = 0.36f;
Mob::Mob()
{
}


Alterable Mob::draw(Renderer* renderer, Alterable alters)
{
	IntersectedEntity::draw(renderer, alters);
	return alters;
}

