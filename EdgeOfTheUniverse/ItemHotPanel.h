#pragma once
#include "Panel.h"
#include "Button.h"
class ItemHotPanel : public Panel
{
public:
	ItemHotPanel();
	~ItemHotPanel();
	
	static int coutItemInHotPanel;// �� ���������� ����� ����� 10, �� ��� �������� ������� �������� ������ 10 ����
	Button** itemSlot;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

