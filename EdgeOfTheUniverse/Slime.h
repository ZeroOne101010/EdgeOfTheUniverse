#pragma once
#include "Entity.h"
class Slime : public Entity
{
public:
	Slime();

	void start() override;
	void update() override;

	virtual Entity* getNewEntity() override;

};

