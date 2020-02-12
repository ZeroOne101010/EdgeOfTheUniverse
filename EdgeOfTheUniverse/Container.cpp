#include "Container.h"

Container::Container()
{
	obj = new RectangleShape(100, 100);
	obj->Position = glm::vec2(0, 0);
	obj->Color = glm::vec4(0.5f, 1, 0.8f, 1);
	obj->Origin = glm::vec2(-obj->Size.x / 2, -obj->Size.y / 2);
	b = new box();
	b->Position = glm::vec2(-100, -100);
}

Container::~Container()
{
	delete obj;
	delete b;
}

void Container::draw(Renderer* renderer, Alterable alters)
{
	alters *= *this;
	renderer->draw(obj, alters);
	renderer->draw(b, alters);
}
