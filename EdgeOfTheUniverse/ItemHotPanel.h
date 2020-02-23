#pragma once
#include "Panel.h"
#include "ItemHotCell.h"
#include "ButtonGroup.h"
class ItemHotPanel : public Panel
{
public:
	ItemHotPanel();
	~ItemHotPanel();
	
	static int coutItemInHotPanel;// �� ���������� ����� ����� 10, �� ��� �������� ������� �������� ������ 10 ����
	ItemHotCell** itemSlot;

	ButtonGroup buttonGroup;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

