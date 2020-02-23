#pragma once
#include "IntersectedEntity.h"
#include "ITakeble.h"
class Item : public IntersectedEntity, public ITakeble
{
public:
	Item();
	int itemID;
	int maxStack;
	// Унаследовано через ITakeble
    void Taked(glm::vec2* position, Inventory* inventory) override;
    void Delete() override;
	virtual void draw(Renderer* renderer, Alterable alters) override;
	virtual void moveToInventory() override;
};

