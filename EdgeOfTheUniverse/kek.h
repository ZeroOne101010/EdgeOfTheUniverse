#pragma once
#include "IDraw.h"
#include "RectangleShape.h"
class kek : public IDraw, public Alterable
{
public:
	kek();
	~kek();
	RectangleShape* lol;
	virtual void draw(Renderer* renderer, Alterable alters) override;
};

