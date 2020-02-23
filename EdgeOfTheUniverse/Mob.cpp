#include "Mob.h"

float Mob::G = 0.15f;
Mob::Mob()
{
}


void Mob::draw(Renderer* renderer, Alterable alters)
{
	IntersectedEntity::draw(renderer, alters);
}

