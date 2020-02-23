#include "Amnis.h"


Amnis::Amnis()
{
	setTexture(Content::sprite_AmnisItem);
	setAllTexture();
}

Entity* Amnis::getNewEntity()
{
	return new Amnis;
}
Alterable Amnis::draw(Renderer* renderer, Alterable alters)
{
	Item::draw(renderer, alters);
	return alters;
}
