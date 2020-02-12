#include "box.h"

box::box()
{
	o = new RectangleShape(50, 50);
	o->Position = glm::vec2(0, 0);
	o->Color = glm::vec4(0.5f, 0.5f, 1, 1);
	o->Origin = glm::vec2(-o->Size.x / 2, -o->Size.y / 2);
	aha = new kek();
	aha->Position = glm::vec2(75, 0);
}

box::~box()
{
	delete o;
	delete aha;
}

void box::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	renderer->draw(o, alters);
	renderer->draw(aha, alters);

}
