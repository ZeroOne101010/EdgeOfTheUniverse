#pragma once
#include "Panel.h"
#include "UIPlayerInterface.h"
class UICanvas : public Panel
{
public:
	UICanvas();
	~UICanvas();

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

