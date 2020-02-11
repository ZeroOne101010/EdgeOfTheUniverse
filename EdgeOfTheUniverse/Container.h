#pragma once
#include "IDraw.h"
#include "RectangleShape.h"
#include "box.h"
class Container : public IDraw, public Alterable
{
public:
	Container();
	RectangleShape* obj;
	box* b;
	virtual void draw(Renderer* renderer, Alterable alters) override;
};

