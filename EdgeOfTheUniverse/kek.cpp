#include "kek.h"

kek::kek()
{
	lol = new RectangleShape(20, 20);
	lol->Position = glm::vec2(0, 0);
	lol->Color = glm::vec4(1, 0.5f, 0.5f, 1);
	lol->Origin = glm::vec2(-lol->Size.x / 2, -lol->Size.y / 2);
}

kek::~kek()
{
	delete lol;
}

void kek::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	renderer->draw(lol, alters);
}
