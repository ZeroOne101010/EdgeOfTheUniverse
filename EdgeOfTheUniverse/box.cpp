#include "box.h"

box::box()
{
	kek = new RectangleShape(50, 50);
	kek->position = glm::vec2(-100, -100);
	kek->color = glm::vec4(0.5f, 0.5f, 1, 1);
	kek->origin = glm::vec2(-kek->size.x / 2, -kek->size.y / 2);
}

void box::draw(Renderer* renderer, Alterable alters)
{
	//alters.alter *= getAlters();
	alters *= *this;
	renderer->draw(kek, alters);
}
