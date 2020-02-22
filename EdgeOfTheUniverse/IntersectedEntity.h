#pragma once
#include "Entity.h"
class IntersectedEntity : public Entity
{
public:
	IntersectedEntity();
	void collisionUpdate();
	virtual void update() override;
};

