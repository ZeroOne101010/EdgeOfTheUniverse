#pragma once
#include "Block.h"
class Air : public Block
{
public:
	Air();

	virtual Block* getNewBlock() override;
};

