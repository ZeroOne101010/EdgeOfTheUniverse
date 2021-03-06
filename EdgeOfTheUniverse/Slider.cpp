#include "Slider.h"

Slider::Slider(vec2 handleSize, vec2 areaSize) : Button(areaSize)
{
	//addDelegates(&eventSlider);
	Color = vec4(230, 230, 230, 255);
	handle.size = handleSize;
	handle.Activable = false;
	handle.Color = vec4(255, 255, 255, 255);
	handle.hoverColor = vec4(225, 225, 225, 255);
	handle.pressColor = vec4(220, 220, 220, 255);
	handle.Origin = vec2(-handle.size.x / 2, -handle.size.y / 2);
	handle.Position = vec2(handle.Position.x, size.y / 2);

	fillArea.size = vec2(fillArea.size.x, size.y);
	fillArea.Color = vec4(0, 255, 149, 255);
}

Slider::~Slider()
{

}

void Slider::handleIsTakeble()
{
	//if (clickBool == true)
	//	handle.pos = vec2(Cursor::getMousePosition(RenderWindow::window).x - (pos.x + origin.x), handle.pos.y);

	//if (handle.pressBool == true)
	//{
	//	if (Cursor::getMousePosition(RenderWindow::window).x - (pos.x + origin.x) >= 0)
	//	{
	//		if (Cursor::getMousePosition(RenderWindow::window).x - (pos.x + origin.x) <= size.x)
	//			handle.pos = vec2(Cursor::getMousePosition(RenderWindow::window).x - (pos.x + origin.x), handle.pos.y);
	//		else
	//			handle.pos = vec2(size.x, handle.pos.y);
	//	}
	//	else handle.pos = vec2(0, handle.pos.y);	
	//}
	//fill = handle.pos.x / size.x;
	//fillArea.size = vec2(handle.pos.x, size.y);
}


Alterable Slider::draw(Renderer* renderer, Alterable alters)
{
	UI::draw(renderer, alters);
	DelegateUpdate();
	handleIsTakeble();
	renderer->draw(&fillArea, alters);
	renderer->draw(&handle, alters);
	return alters;
}
