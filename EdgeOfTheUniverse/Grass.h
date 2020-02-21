#pragma once
#include "Block.h"
#include "TBO.h"
class Grass : public Block
{
public:
	Grass();
	virtual Block* getNewBlock() override;
	virtual void start() override;
	virtual void update() override;

};

