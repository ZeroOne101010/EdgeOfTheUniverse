#pragma once
#include "Mob.h"
#include "Block.h"
class Player : public Mob
{
public:
	Player();
	virtual Entity* getNewEntity() override;
};

