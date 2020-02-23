#pragma once
#include "IntersectedEntity.h"
#include "ITakeble.h"
class Item : public IntersectedEntity, public ITakeble
{
public:
	Item();
	int stuck = 64;
	virtual void Taked(Alterable* ownerAlter, glm::vec2* ownerOffset, Inventory* ownerInventory) override;
	virtual void GiveToInventory() override;
	virtual void Delete() override;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;





};

