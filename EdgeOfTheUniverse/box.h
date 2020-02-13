#pragma once
#include "IDraw.h"
#include "RectangleShape.h"
#include "kek.h"
class box : public IDraw, public Alterable
{
public:
	box();
	~box();
	float k;
	RectangleShape* o;
	kek* aha;
	virtual void draw(Renderer* renderer, Alterable alters) override;

};

