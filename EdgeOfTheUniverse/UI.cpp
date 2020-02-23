#include "UI.h"

UI::UI()
{
	carcass = new RectangleShape(size);
}

UI::UI(vec2 size)
{
	carcass = new RectangleShape(size);
	this->size = size;
}

UI::~UI()
{
	delete carcass;
}

Alterable UI::draw(Renderer* renderer, Alterable alters)
{
	alters *= this;
	CarcassUpdate();
	carcass->Size = size;
	if (buttonAttached)
	{
		alters.Position = vec2(alters.Position.x, RenderWindow::height - alters.Position.y - size.y);
	}
	if (rightAttached)
	{
		alters.Position = vec2(RenderWindow::width - alters.Position.x - size.x, alters.Position.y);
	}
	if (carcassIsActive == true)
		renderer->draw(carcass, alters);
	return alters;
}

void UI::CarcassUpdate()
{
	carcass->Size = size;
	carcass->Color = Color;
	if (isChangedColor == false)
	{
		carcass->Color = Color;
	}
	else 
	{
		carcass->Color = otherColor;
	}

}
