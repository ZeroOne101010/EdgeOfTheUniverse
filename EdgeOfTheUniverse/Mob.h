#pragma once
#include "IntersectedEntity.h"
class Mob : public IntersectedEntity
{
public:

	static float G;

	Mob();

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;

};

