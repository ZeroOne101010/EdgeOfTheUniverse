#include "Item.h"

Item::Item()
{
	rect->Size = glm::vec2(Block::sizeBlock, Block::sizeBlock);
}

void Item::Take()
{
	delete this;
}

Alterable Item::draw(Renderer* renderer, Alterable alters)
{
	IntersectedEntity::draw(renderer, alters);
	return alters;
}

