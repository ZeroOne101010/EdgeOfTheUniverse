#include "IDraw.h"
#include "Renderer.h"

void Renderer::draw(IDraw* obj, Alterable alters)
{
	obj->draw(this, alters);
}
