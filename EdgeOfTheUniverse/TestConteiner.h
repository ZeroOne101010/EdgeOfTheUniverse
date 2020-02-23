#pragma once
#include "UI.h"
#include "Button.h"
class TestConteiner : public UI
{
public:
	TestConteiner();
	Button* but;
	//virtual Alterable draw(Renderer* renderer, Alterable alters) override;

	virtual void Draw(Renderer* renderer, Alterable alters) override;
};

