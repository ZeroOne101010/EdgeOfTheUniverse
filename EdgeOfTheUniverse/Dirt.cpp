#include "Content.h"
#include "Dirt.h"

Dirt::Dirt()
{
	//rect.Color = glm::vec4(153, 108, 75, 255);
	texture = Content::spriteList_Grass;
	textureRect = FloatRect(16 + 2, 0, 16, 16);
	color = glm::vec4(255, 255, 255, 255);
}

Block* Dirt::getNewBlock()
{
	return new Dirt();
}
