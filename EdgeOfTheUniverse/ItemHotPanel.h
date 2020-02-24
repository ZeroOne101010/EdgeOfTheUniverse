#pragma once
#include "Panel.h"
#include "ItemHotCell.h"
#include "ButtonGroup.h"
#include "Controller.h"
#include "IInventory.h"
#include "RegisteryEntity.h"
class ItemHotPanel : public Panel
{
public:
	ItemHotPanel(Controller* controller);
	~ItemHotPanel();
	
	static int coutItemInHotPanel;// �� ���������� ����� ����� 10, �� ��� �������� ������� �������� ������ 10 ����
	ItemHotCell** itemSlot;
	Controller* controller;
	ButtonGroup buttonGroup;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
private:
	void UpdateCells();
};

