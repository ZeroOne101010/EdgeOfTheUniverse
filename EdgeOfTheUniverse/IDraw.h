#pragma once
#include "Renderer.h"
class IDraw 
{
public:
	virtual void draw(Renderer* renderer, Alterable alters) = 0;
};

