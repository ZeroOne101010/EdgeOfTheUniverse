#include "Button.h"
#include "EventSetWhite.h"

EventSetWhite::EventSetWhite(Button* but)
{
	this->but = but;
}

EventSetWhite::~EventSetWhite()
{
	delete but;
}

void EventSetWhite::onClick()
{
	but->eventBool[0] = !but->eventBool[0];
	if (but->Activable == true) 
	{
		but->isActive = !but->isActive;
		if (but->buttonGroup != nullptr)
			but->buttonGroup->selectedIndex = but->indexInGroup;
	}

}
void EventSetWhite::upClick()
{

}
void EventSetWhite::onHover()
{
	if (but->Activable == true)
	{
		if (but->isActive == false)
		{
			but->otherColor = but->hoverColor;
			but->isChangedColor = true;
		}
		else
		{
			but->otherColor = but->hoverActivetedColor;
			but->isChangedColor = true;
		}
	}else
	{
		but->otherColor = but->hoverColor;
		but->isChangedColor = true;
	}


}

void EventSetWhite::upHover()
{
	if (but->Activable == true)
	{
		if (but->isActive == false)
		{
			but->isChangedColor = false;
		}
		else
		{
			but->otherColor = but->activetedColor;
			but->isChangedColor = true;
		}
	}
	else
	{
		but->isChangedColor = false;
	}
}

void EventSetWhite::press()
{
	if (but->Activable == true) 
	{
		if (but->isActive == false)
		{
			but->otherColor = but->pressColor;
		}
		else
		{
			but->otherColor = but->pressActivetedColor;

		}
	}
	else 
	{
		but->otherColor = but->pressColor;
	}
	but->isChangedColor = true;

}

