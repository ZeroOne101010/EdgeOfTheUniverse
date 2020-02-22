#include "Grass.h"

Grass::Grass() : Block(glm::vec4(255, 255, 255, 255), Content::spriteList_Grass, FloatRect(0, 0, 16, 16))
{
	
}

Block* Grass::getNewBlock()
{
	return new Grass();
}

void Grass::start()
{
}

void Grass::update()
{
}
