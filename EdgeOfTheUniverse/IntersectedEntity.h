#pragma once
#include "Entity.h"
class IntersectedEntity : public Entity
{
public:
	IntersectedEntity();
	void collisionUpdate();
	virtual void draw(Renderer* renderer, Alterable alters) override;
	static float G;
};

