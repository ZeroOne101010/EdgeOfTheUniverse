#include "Button.h"
#include "ButtonGroup.h"

ButtonGroup::ButtonGroup()
{

}

void ButtonGroup::UpdateButtonGroup()
{

}

void ButtonGroup::operator+=(Button* but)
{
	but->buttonGroup = this;
	buttons.push_back(but);
	but->indexInGroup = buttons.size() - 1;
}

void ButtonGroup::Add(Button* but)
{
	but->buttonGroup = this;
	buttons.push_back(but);
	but->indexInGroup = buttons.size() - 1;
}
