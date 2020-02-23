#pragma once
#include "Mob.h"
class Slime : public Mob
{
public:
	Slime();


	virtual Entity* getNewEntity() override;

};

