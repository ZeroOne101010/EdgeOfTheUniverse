#include "ItemHotPanel.h"

int ItemHotPanel::coutItemInHotPanel = 10;

ItemHotPanel::ItemHotPanel()
{
	itemSlot = new ItemHotCell * [coutItemInHotPanel];
	int offset = 5;
	for (int x = 0; x < coutItemInHotPanel; x++)
	{
		itemSlot[x] = new ItemHotCell();
		buttonGroup.Add(itemSlot[x]);
		itemSlot[x]->Position = vec2(x * (itemSlot[x]->size.x + offset) + offset, offset);
	}
	size = vec2((itemSlot[0]->size.x + offset) * coutItemInHotPanel + offset, itemSlot[0]->size.y + offset * 2);
}

ItemHotPanel::~ItemHotPanel()
{
	delete[coutItemInHotPanel] itemSlot;
}

Alterable ItemHotPanel::draw(Renderer* renderer, Alterable alters)
{
	alters = Panel::draw(renderer, alters);
	for (int x = 0; x < coutItemInHotPanel; x++)
	{
		renderer->draw(itemSlot[x], alters);
	}
	return alters;
}
