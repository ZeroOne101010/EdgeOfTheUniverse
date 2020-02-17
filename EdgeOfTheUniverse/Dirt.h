#pragma once
#include "Block.h"
class Dirt : public Block
{
public:
	Dirt();

	virtual Block* getNewBlock() override;

};

