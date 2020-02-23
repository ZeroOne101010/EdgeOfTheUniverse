#pragma once
#include "IntersectedEntity.h"
#include "IInventory.h"
#include "RegisteryEntity.h"
class InventoredEntity : public IntersectedEntity, public IInventory
{
public:
	virtual void Take(ITakeble* target, int id) override;
};

