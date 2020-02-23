#pragma once
#include "Item.h"
#include "Content.h"
class Stone_Sword : public Item
{
public:
	Stone_Sword();
	virtual Entity* getNewEntity() override;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

