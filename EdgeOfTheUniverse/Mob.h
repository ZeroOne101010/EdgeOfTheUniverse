#pragma once
#include "IntersectedEntity.h"
class Mob : public IntersectedEntity
{
public:
	Mob();

	virtual void draw(Renderer* renderer, Alterable alters) override;

};

