#include "Item.h"
#include "World.h"
#include "Inventory.h"

Item::Item()
{
	rect->Size = glm::vec2(Block::sizeBlock, Block::sizeBlock);
}

void Item::Taked(Alterable* ownerAlter, glm::vec2* ownerOffset, Inventory* ownerInventory)
{
	this->ownerAlter = ownerAlter;
	this->ownerOffset = ownerOffset;
	this->ownerInventory = ownerInventory;
	taked = true;
}
void Item::GiveToInventory()
{
	FloatRect rect(Position, rect->Size);
	FloatRect ownerRect(ownerAlter->Position, *ownerOffset);
	bool alreadyTaked = false;
	int slot = 0;
	if (rect.Intersects(ownerRect))
	{
		if (ownerInventory->full == false)
		{
			if (ownerInventory->slots.size() > 0)
			{
				for (slot = 0; slot < ownerInventory->slots.size(); slot++)
				{
					if (ownerInventory->slots[slot].id == id)
					{
						if (ownerInventory->slots[slot].stuckCount < stuck)
						{
							ownerInventory->slots[slot].stuckCount++;
							alreadyTaked = true;
							Delete();
							break;
						}
					}
				}

				if (alreadyTaked == false)
				{
					if (ownerInventory->slots.size() < ownerInventory->maxSlots)
					{
						ownerInventory->slots.push_back(ItemConteiner(id, stuck));
						alreadyTaked = true;
						Delete();
					}
					else
					{
						ownerInventory->full = true;
					}
				}
			}
			else
			{
				ownerInventory->slots.push_back(ItemConteiner(id, stuck));
				alreadyTaked = true;
				Delete();
			}

		}
		else
		{
			std::cout << "Inventory full" << std::endl;
		}
	}
}
void Item::Delete()
{
	for (int i = 0; i < world->entity.size(); i++)
	{
		if (world->entity[i] == this)
		{
			world->entity.erase(world->entity.begin() + i);
		}
	}
}

Alterable Item::draw(Renderer* renderer, Alterable alters)
{
	IntersectedEntity::draw(renderer, alters);
	if(taked == true)
	GiveToInventory();
	return alters;
}






