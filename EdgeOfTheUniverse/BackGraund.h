#pragma once
#include <vector>
#include "AlterableHeader.h"
#include "BackGroundLayer.h"
class BackGraund : public IDraw, public Alterable
{
public:
	BackGraund();
	std::vector<BackGroundLayer> layers;
	float speed;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;

};

