#include "ItemHotCell.h"
#include "Cursor.h"
#include "Content.h"
ItemHotCell* Cursor::grappedInventoryCell;

Cursor::Cursor()
{
	keepedItem = new RectangleShape(16, 16);
	keepedItem->Origin = vec2(-keepedItem->Size.x / 2, -keepedItem->Size.y / 2);
	keepedItem->Color = vec4(255, 255, 255, 255);
}

bool Cursor::Intersect(Alterable* alterable, float offsetX, float offsetY, GLFWwindow* window)
{
	if ((getMousePosition(window).x > alterable->globalPosition.x) && (getMousePosition(window).x < alterable->globalPosition.x + offsetX))
	{
		if ((getMousePosition(window).y > alterable->globalPosition.y) && (getMousePosition(window).y < alterable->globalPosition.y + offsetY))
		{
			return true;
		}
	}
	else
	{
		return false;
	}	
	return false;
}

bool Cursor::Intersect(UI* ui, GLFWwindow* window)
{
	if ((getMousePosition(window).x > ui->globalPosition.x) && (getMousePosition(window).x < ui->globalPosition.x + ui->size.x))
	{
		if ((getMousePosition(window).y > ui->globalPosition.y) && (getMousePosition(window).y < ui->globalPosition.y + ui->size.y))
		{
			return true;
		}
	}
	else
	{
		return false;
	}
	return false;
}

glm::vec2 Cursor::getMousePosition(GLFWwindow* window)
{
	double width, height;
	glfwGetCursorPos(window, &width, &height); 
	return glm::vec2(width, height);
}
void Cursor::Update()
{
	keepedItem->Position = Cursor::getMousePosition(RenderWindow::window);
	keepedItem->Size = grappedInventoryCell->carcass->Size;
	keepedItem->Origin = vec2(-keepedItem->Size.x / 2, -keepedItem->Size.y / 2);
	keepedItem->textureRect = grappedInventoryCell->item->carcass->textureRect;
	keepedItem->tbo = grappedInventoryCell->item->carcass->tbo;
}
Alterable Cursor::draw(Renderer* renderer, Alterable alters)
{
	if (grappedInventoryCell != nullptr)
	{
		Update();
		renderer->draw(keepedItem, alters);
	}
	return  alters;
}


