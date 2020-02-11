#pragma once
#include "IDraw.h"
#include "RectangleShape.h"
class box : public IDraw, public Alterable
{
public:
	box();
	RectangleShape* kek;
	virtual void draw(Renderer* renderer, Alterable alters) override;

};

