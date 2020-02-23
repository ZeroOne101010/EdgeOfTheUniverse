#pragma once
#include "Entity.h"
class IntersectedEntity : public Entity
{
public:
	IntersectedEntity();
	void collisionUpdate();
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
	static float G;
};

