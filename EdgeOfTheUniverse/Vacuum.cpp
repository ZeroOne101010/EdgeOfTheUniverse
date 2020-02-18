#include "Vacuum.h"

Vacuum::Vacuum()
{
	color = glm::vec4(200, 100, 200, 150);
}

Block* Vacuum::getNewBlock()
{
	return new Vacuum();
}
