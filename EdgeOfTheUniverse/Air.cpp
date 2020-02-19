#include "Air.h"

Air::Air()
{
	canUpdateTexture = false;
	color = glm::vec4(0, 0, 0, 0);
}

Block* Air::getNewBlock()
{
	return new Air();
}
