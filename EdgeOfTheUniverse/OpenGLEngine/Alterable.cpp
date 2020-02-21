#include "Alterable.h"
Alterable Alterable::Default;

Alterable Alterable::operator*=(Alterable* alter)
{
	Origin = alter->Origin + Origin;
	glm::vec2 p = (alter->Position + Origin) * RelSize;
	Position += glm::vec2(p.x * cos(Angle) - p.y * sin(Angle), p.x * sin(Angle) + p.y * cos(Angle));

	Angle += alter->Angle;
	RelSize *= alter->RelSize;
	alter->globalPosition = Position;
	return *this;
}
