#include "glm/glm.hpp"
#include "RegisteryEntity.h"
#include "ItemConteiner.h"
#include "Item.h"

Item::Item()
{
	rect->Size = glm::vec2(Block::sizeBlock, Block::sizeBlock);
}

void Item::draw(Renderer* renderer, Alterable alters)
{
	IntersectedEntity::draw(renderer, alters);
	moveToInventory();
}

void Item::moveToInventory()
{
	if (taked)
	{
		Position += vec2(1, 0);
		FloatRect inventoryOwnerRect(takedInventory->ownerShape->Position, takedInventory->ownerShape->Size);
		if (takedInventory->inventoryFull == false)
		{
			if (Position.x > inventoryOwnerRect.positionX& Position.x < inventoryOwnerRect.positionX + inventoryOwnerRect.sizeX)
				if (Position.y > inventoryOwnerRect.positionY& Position.y < inventoryOwnerRect.positionY + inventoryOwnerRect.sizeY)
				{
					float alreadyGet = false;
					for (int i = 0; i < takedInventory->inventoryItems.size(); i++)
					{
						if (takedInventory->inventoryItems[i].id == id + RegisteryEntity::mobsCount)
						{
							if (alreadyGet == false)
							{
								if (takedInventory->inventoryItems[i].count < maxStack)
								{
									takedInventory->inventoryItems[i].count++;
									alreadyGet = true;
									Delete();
								}
							}
						}
						else
						{
							if (alreadyGet == false)
							{
								if (takedInventory->fullSlots < takedInventory->maxSlots)
								{
									ItemConteiner item(id + RegisteryEntity::mobsCount, 1);
									takedInventory->inventoryItems.push_back(item);
									alreadyGet = true;
									takedInventory->fullSlots++;
									if (takedInventory->fullSlots >= takedInventory->maxSlots)
										takedInventory->inventoryFull = true;
									Delete();
								}
							}
						}
					}
				}
		}
	}
}

void Item::Taked(glm::vec2* position, Inventory* inventory)
{
	takedPosition = position;
	takedInventory = inventory;
	taked = true;
}

void Item::Delete()
{
}


