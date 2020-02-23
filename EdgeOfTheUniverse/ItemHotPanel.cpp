#include "ItemHotPanel.h"

int ItemHotPanel::coutItemInHotPanel = 10;

ItemHotPanel::ItemHotPanel()
{
	itemSlot = new Button *[coutItemInHotPanel];
	for (int x = 0; x < coutItemInHotPanel; x++)
	{
		itemSlot[x] = new Button(vec2(100, 100));
		itemSlot[x]->Color = vec4(255, 255, 255, 255);
		//itemSlot[x].Color = vec4(255, 150, 150, 255);
		int offsetX = 5;
		int offsetY = 2;
		itemSlot[x]->size = vec2(54, 54 - offsetY);
		itemSlot[x]->pos = vec2(x * (itemSlot[x]->size.x + offsetX) + offsetX, -itemSlot[x]->size.y - 4);
	}
}

ItemHotPanel::~ItemHotPanel()
{
	delete[coutItemInHotPanel] itemSlot;
}

Alterable ItemHotPanel::draw(Renderer* renderer, Alterable alters)
{
	Panel::draw(renderer, alters);
	for (int x = 0; x < coutItemInHotPanel; x++)
	{
		renderer->draw(itemSlot[x], alters);
	}
	return alters;
}
