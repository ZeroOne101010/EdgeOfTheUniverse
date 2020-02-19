#include "Content.h"
#include "Dirt.h"

Dirt::Dirt() : Block(glm::vec4(255, 255, 255, 255), Content::spriteList_Dirt, FloatRect(16 + 2, 0, 16, 16))
{

}

Block* Dirt::getNewBlock()
{
	return new Dirt();
}
