#include "TestConteiner.h"

TestConteiner::TestConteiner() : UI(vec2(100, 100))
{
	but = new Button(vec2(50, 50));
}

//Alterable TestConteiner::draw(Renderer* renderer, Alterable alters)
//{
//
//	return Alterable();
//}

void TestConteiner::Draw(Renderer* renderer, Alterable alters)
{
	//Alterable kek = UI::draw(renderer, alters);
	renderer->draw(but, alters);
}

