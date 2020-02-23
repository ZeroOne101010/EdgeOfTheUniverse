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
void Amnis::draw(Renderer* renderer, Alterable alters)
{
	Item::draw(renderer, alters);
}
