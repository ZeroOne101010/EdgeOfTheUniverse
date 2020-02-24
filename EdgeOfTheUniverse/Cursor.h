#pragma once
#include "AlterableHeader.h"
#include "glm/vec2.hpp"
#include "OpenGLEngine/RenderWindow.h"
#include "UI.h"
#include "OpenGLEngine/RectangleShape.h"
#include "AlterableHeader.h"
class ItemHotCell;
class Cursor : public IDraw
{
public:
	Cursor();
	RectangleShape* keepedItem;
	static bool Intersect(Alterable* alterable, float offsetX, float offsetY, GLFWwindow* window);
	static bool Intersect(UI* ui, GLFWwindow* window);
	static glm::vec2 getMousePosition(GLFWwindow* window);
	static ItemHotCell* grappedInventoryCell;
	virtual Alterable draw(Renderer* renderer, Alterable alters) override;
private:
	void Update();
};

