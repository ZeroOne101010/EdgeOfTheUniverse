#include "Slime.h"

Slime::Slime()
{
	rect->Color = glm::vec4(150, 255, 150, 230);
}

Entity* Slime::getNewEntity()
{
	return new Slime();
}
