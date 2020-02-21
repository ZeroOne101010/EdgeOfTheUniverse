#pragma once
#include <vector>
class Button;
class ButtonGroup
{
public:
	ButtonGroup();
	void UpdateButtonGroup();
	int selectedIndex;
	std::vector<Button*> buttons;
	void operator+=(Button* but);
	void Add(Button* but);
};

