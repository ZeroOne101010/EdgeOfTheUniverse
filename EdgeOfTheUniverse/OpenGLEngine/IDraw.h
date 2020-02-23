#pragma once
#include "Renderer.h"
class IDraw 
{
public:
	virtual Alterable draw(Renderer* renderer, Alterable alters) = 0;
};

