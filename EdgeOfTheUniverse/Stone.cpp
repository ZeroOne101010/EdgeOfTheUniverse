#include "Stone.h"

Stone::Stone()
{
	texture = Content::SpriteList_Stone;
	color = glm::vec4(255, 255, 255, 255);
}

Block* Stone::getNewBlock()
{
	return new Stone();
}
