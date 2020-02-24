#include "Button.h"

Button::Button()
{
	buttonGroup = nullptr;
	whiteEvent = new EventSetWhite(this);
	addDelegates(whiteEvent);
}

Button::Button(vec2 size) : UI(size)
{
	whiteEvent = new EventSetWhite(this);
	addDelegates(whiteEvent);
}
Button::~Button()
{
	delete[4] eventBool;
}
void Button::addDelegates(IButton* obj)
{
	Delegates.push_back(obj);
}
void Button::DelegateUpdate()
{
	clickBool = false;
	if (Cursor::Intersect(this, RenderWindow::window) == true)
	{
		hoverBool = true;
		for (int i = 0; i < Delegates.size(); i++)
		{
			Delegates[i]->onHover();
			if (RenderWindow::mouseLeft == true)
			{
				pressOnButtonBool = true;
				Delegates[i]->press();
				pressBool = true;
				if (Delegates[i]->blockClickLeft == false)
				{
					Delegates[i]->onClick();
					clickBool = true;
					Delegates[i]->blockClickLeft = true;
				}
				Delegates[i]->blockUpClickLeft = true;
			}
			else 
			{
				pressOnButtonBool = false;
				pressBool = false;
				if (Delegates[i]->blockUpClickLeft == true)
				{
					Delegates[i]->upClick();
					Delegates[i]->blockUpClickLeft = false;
				}
				Delegates[i]->blockClickLeft = false;
			}
		}
	}
	else 
	{
		pressOnButtonBool = false;
		if (RenderWindow::mouseLeft == false)
			pressBool = false;
		for (int i = 0; i < Delegates.size(); i++)
		{
			hoverBool = false;
			Delegates[i]->upHover();
			Delegates[i]->blockClickLeft = false;
		}
	}
}
void Button::Draw(Renderer* renderer, Alterable alters)
{
}
Alterable Button::draw(Renderer* renderer, Alterable alters)
{
	alters = UI::draw(renderer, alters);
	DelegateUpdate();
	if (buttonGroup != nullptr)
	{
		if (indexInGroup == buttonGroup->selectedIndex)
		{
			isActive = true;
		}
		else
		{
			isActive = false;
		}
	}
	return alters;

}
