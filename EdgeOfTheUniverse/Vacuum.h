#pragma once
#include "Block.h"
class Vacuum : public Block
{
public:
	Vacuum();
	virtual Block* getNewBlock() override;

};

