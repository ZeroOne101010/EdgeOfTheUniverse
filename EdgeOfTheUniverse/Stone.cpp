#include "Stone.h"

Stone::Stone()
{
	color = glm::vec4(150, 150, 150, 255);
}

Block* Stone::getNewBlock()
{
	return new Stone();
}
