#pragma once
#include "OpenGLEngine/RectangleShape.h"
#include "Inventory.h"
class ITakeble
{
public:
	virtual void Taked(Alterable* ownerAlter, glm::vec2* ownerOffset, Inventory* ownerInventory) = 0;
	virtual void GiveToInventory() = 0;
	virtual void Delete() = 0;
	Alterable* ownerAlter;
	glm::vec2* ownerOffset;
	Inventory* ownerInventory;
	bool taked;
};