#pragma once
#include "glm/vec2.hpp"
#include "Inventory.h"
class ITakeble
{
public:
	virtual void Taked(glm::vec2* position, Inventory* inventory) = 0;
	virtual void moveToInventory() = 0;
	Inventory* takedInventory;
	glm::vec2* takedPosition;
	bool taked;
	virtual void Delete() = 0;
};