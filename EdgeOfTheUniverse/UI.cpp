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
	CarcassUpdate();
	//Position = vec2((rightAttached ? RenderWindow::width : 0) + pos.x - (rightAttached ? size.x : 0), (buttonAttached ? RenderWindow::height : 0) + pos.y - (buttonAttached ? size.y : 0));
	Position = vec2((rightAttached ? RenderWindow::width : 0) + pos.x, (buttonAttached ? RenderWindow::height : 0) + pos.y);
	//Origin = vec2((rightAttached ? -size.x : 0) + origin.x, (buttonAttached ? -size.y : 0) + origin.y);
	//Origin = origin;
	carcass->Size = size;
	alters *= this;
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
