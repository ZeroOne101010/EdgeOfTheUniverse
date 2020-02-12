#include "box.h"

box::box()
{
	o = new RectangleShape(50, 50);
	o->Position = glm::vec2(0, 0);
	o->color = glm::vec4(0.5f, 0.5f, 1, 1);
	o->Origin = glm::vec2(-o->size.x / 2, -o->size.y / 2);
	aha = new kek();
	aha->Position = glm::vec2(75, 0);
}

void box::draw(Renderer* renderer, Alterable alters)
{
	//alters.alter *= getAlters();
	alters *= *this;
	std::cout << alters.ParentPostion.x << std::endl;
	//renderer->draw(still, alters);
	renderer->draw(o, alters);
	renderer->draw(aha, alters);

}
