#pragma once
#include "IntersectedEntity.h"
class Mob : public IntersectedEntity
{
public:

	static float G;

	Mob();

	virtual void draw(Renderer* renderer, Alterable alters) override;

};

