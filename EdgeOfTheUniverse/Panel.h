#pragma once
#include "UI.h"
class Panel : public UI
{
public:
	Panel(vec2 size);
	Panel();
	// �� ����� ������ alters *= *this;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;


	// ������������ ����� UI
	virtual void Draw(Renderer* renderer, Alterable alters) override;

};

