#include "BackGraund.h"

BackGraund::BackGraund()
{

}

Alterable BackGraund::draw(Renderer* renderer, Alterable alters)
{
	alters *= this;
	for (int i = 0; i < layers.size(); i++)
	{
		renderer->draw(&layers[i], alters);
	}
	return alters;
}
