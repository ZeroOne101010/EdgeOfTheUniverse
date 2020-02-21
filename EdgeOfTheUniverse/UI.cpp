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

void UI::draw(Renderer* renderer, Alterable alters)
{
	CarcassUpdate();
	Position = vec2((rightAttached ? RenderWindow::width : 0) + pos.x, (buttonAttached ? RenderWindow::height : 0) + pos.y);
	Origin = vec2((rightAttached ? -size.x : 0) + origin.x, (buttonAttached ? -size.y : 0) + origin.y);
	alters *= this;
	if (carcassIsActive == true)
		renderer->draw(carcass, alters);
	Draw(renderer, *this);
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
