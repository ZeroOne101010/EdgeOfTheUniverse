#pragma once
#include "Panel.h"
#include "ItemHotPanel.h"

class World;
class Entity;

class UIPlayerInterface : public Panel
{
public:
	UIPlayerInterface(World* world, Entity* player);
	~UIPlayerInterface();

	World* world;
	Entity* player;

	ItemHotPanel* itemHotPanel;

	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
};

