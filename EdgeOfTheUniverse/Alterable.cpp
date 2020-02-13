#include "Alterable.h"
Alterable Alterable::Default;

Alterable::~Alterable()
{
}

Alterable Alterable::operator*=(Alterable alter)
{
	Origin = alter.Origin + Origin;
	//glm::vec4 Position4 = (Rotation * (glm::vec4(alter.Position.x, alter.Position.y, 0, 1) + glm::vec4(Origin.x, Origin.y, 0, 0))) * glm::vec4(RelSize.x, RelSize.y, 0, 1);
	
	glm::vec2 p = (alter.Position + Origin) * RelSize;
	Position += glm::vec2(p.x * cos(Angle) - p.y * sin(Angle), p.x * sin(Angle) + p.y * cos(Angle));

	Angle += alter.Angle;
	RelSize *= alter.RelSize;
	return *this;
}
