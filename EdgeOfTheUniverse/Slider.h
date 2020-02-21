#pragma once
#include "UI.h"
#include "Button.h"
#include "Panel.h"
class Slider : public Button
{
public:
	Slider(vec2 handleSize, vec2 areaSize);
	~Slider();
	void handleIsTakeble();
	Button handle = Button();
	Panel fillArea = Panel();
	float fill;
	virtual void Draw(Renderer* renderer, Alterable alters) override;
};

