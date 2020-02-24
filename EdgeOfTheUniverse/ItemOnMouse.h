#pragma once
#include "OpenGLEngine/RectangleShape.h"
#include "AlterableHeader.h"
#include "Cursor.h"

class World;

class ItemOnMouse : public Alterable, public IDraw
{
public:
	ItemOnMouse(World* world);
	~ItemOnMouse();

	World* world;

	RectangleShape* itemRect;
	int idItem;
	int countItems;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;

};

