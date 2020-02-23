#pragma once
#include "AlterableHeader.h"
#include "OpenGLEngine/RectangleShape.h"
#include "OpenGLEngine/RenderWindow.h"
using namespace glm;
class UI : public Alterable, public IDraw
{
public:
	UI();
	UI(vec2 size);
	~UI();
	vec2 size = vec2(100, 100);
	vec2 pos;
	vec2 origin;
	vec4 Color = vec4(255, 255, 255, 255);
	vec4 otherColor;
	bool isChangedColor = false;
	bool rightAttached = false;
	bool buttonAttached = false;
	bool carcassIsActive = true;
    RectangleShape* carcass;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
private:
	void CarcassUpdate();

};

