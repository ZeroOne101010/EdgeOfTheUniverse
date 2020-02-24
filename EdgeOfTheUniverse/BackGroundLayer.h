#pragma once
#include "AlterableHeader.h"
#include "OpenGLEngine/RectangleShape.h"
#include "glm/vec2.hpp"
class World;
class BackGroundLayer : public IDraw, public Alterable
{
public:
	BackGroundLayer(World* world, glm::vec2 speed, glm::vec2 size);
	glm::vec2 speed;
	World* world;
	RectangleShape layer = RectangleShape(glm::vec2(100, 100));
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

