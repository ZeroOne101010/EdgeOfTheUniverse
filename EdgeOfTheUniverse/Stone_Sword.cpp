#include "Stone_Sword.h"

Stone_Sword::Stone_Sword()
{
	rect->Size = glm::vec2(32, 32);
	setTexture(Content::SpriteList_Tools);
	textureRect = FloatRect(glm::vec2(32 + 2, 0), glm::vec2(32, 32));
}

Entity* Stone_Sword::getNewEntity()
{
	return new Stone_Sword();
}

Alterable Stone_Sword::draw(Renderer* renderer, Alterable alters)
{
	Item::draw(renderer, alters);
	return alters;
}
