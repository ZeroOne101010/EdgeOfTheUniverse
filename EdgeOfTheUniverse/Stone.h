#pragma once
#include "Block.h"
class Stone : public Block
{
public:
	Stone();
	virtual Block* getNewBlock() override;
};

