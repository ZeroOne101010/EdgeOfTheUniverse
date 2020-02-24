#include "Panel.h"
#include "Content.h"
#include "ItemHotCell.h"

ItemHotCell::ItemHotCell()
{
	this->size = vec2(38, 38);
	int offset = 6;
	Color = vec4(255, 255, 255, 150);
	hoverColor = vec4(255, 255, 255, 200);
	item = new Panel(vec2(size.x - offset, size.y - offset));
	item->Color = vec4(255, 255, 255, 0);
	item->Position = vec2((size.x - item->size.x) / 2, (size.y - item->size.y) / 2);
	//item->carcass->tbo = Content::spriteList_Grass;
	//item->carcass->textureRect = FloatRect(9 * (16 + 2), 3 * (16 + 2), 16, 16);
}

ItemHotCell::~ItemHotCell()
{
	delete item;
}

Alterable ItemHotCell::draw(Renderer* renderer, Alterable alters)
{
	alters = Button::draw(renderer, alters);
	renderer->draw(item, alters);
	return Alterable();
}