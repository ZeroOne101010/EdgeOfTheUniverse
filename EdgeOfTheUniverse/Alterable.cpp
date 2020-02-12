#include "Alterable.h"
Alterable Alterable::Default;

Alterable::~Alterable()
{
}

Alterable Alterable::operator*=(Alterable alter)
{
	ParentPostion = (alter.Position + alter.Origin) * RelSize;
	Origin = alter.Origin + Origin;
	glm::vec4 Position4 = (Rotation * (glm::vec4(alter.Position.x, alter.Position.y, 0, 1) + glm::vec4(Origin.x, Origin.y, 0, 0))) * glm::vec4(RelSize.x, RelSize.y, 0, 1);
	Rotation *= alter.Rotation;
	Position += glm::vec2(Position4.x, Position4.y);
	RelSize *= alter.RelSize;
	return *this;
}
