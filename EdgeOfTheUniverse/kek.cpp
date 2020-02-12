#include "kek.h"

kek::kek()
{
	lol = new RectangleShape(20, 20);
	lol->Position = glm::vec2(0, 0);
	lol->color = glm::vec4(1, 0.5f, 0.5f, 1);
	lol->Origin = glm::vec2(-lol->size.x / 2, -lol->size.y / 2);
}

void kek::draw(Renderer* renderer, Alterable alters)
{
	//alters.alter *= getAlters();
	alters *= *this;
	//renderer->draw(still, alters);
	renderer->draw(lol, alters);
}
