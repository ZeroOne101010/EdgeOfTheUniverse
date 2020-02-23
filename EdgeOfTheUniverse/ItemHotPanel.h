#pragma once
#include "Panel.h"
#include "Button.h"
class ItemHotPanel : public Panel
{
public:
	ItemHotPanel();
	~ItemHotPanel();
	
	static int coutItemInHotPanel;// Их количиство будет равно 10, тк для быстрого доступа доступно только 10 цифр
	Button** itemSlot;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

