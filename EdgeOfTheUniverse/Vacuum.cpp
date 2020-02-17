#include "Vacuum.h"

Vacuum::Vacuum()
{
	color = glm::vec4(100, 100, 100, 150);
}

Block* Vacuum::getNewBlock()
{
	return new Vacuum();
}
