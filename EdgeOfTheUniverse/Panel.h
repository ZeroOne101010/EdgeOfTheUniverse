#pragma once
#include "UI.h"
class Panel : public UI
{
public:
	Panel(vec2 size);
	Panel();
	// Не нужно писать alters *= *this;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;


	// Унаследовано через UI
	virtual void Draw(Renderer* renderer, Alterable alters) override;

};

