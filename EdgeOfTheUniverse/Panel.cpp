#include "Panel.h"

Panel::Panel(vec2 size) : UI(size)
{

}

Panel::Panel()
{

}

Alterable Panel::draw(Renderer* renderer, Alterable alters)
{
	alters = UI::draw(renderer, alters);
	return alters;
}

void Panel::Draw(Renderer* renderer, Alterable alters)
{
}
