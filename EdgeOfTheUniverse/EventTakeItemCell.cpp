#include "ItemHotCell.h"
#include "UIPlayerInterface.h"
#include "EventTakeItemCell.h"

EventTakeItemCell::EventTakeItemCell(UIPlayerInterface* playerInterface)
{
	this->playerInterface = playerInterface;
}

void EventTakeItemCell::onClick()
{

}

void EventTakeItemCell::upClick()
{
	//playerInterface->itemHotPanel->itemOnMouse->itemRect->Color = vec4(255, 255, 0, 255);
}

void EventTakeItemCell::onHover()
{
}

void EventTakeItemCell::upHover()
{
}

void EventTakeItemCell::press()
{
}
