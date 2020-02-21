#include "Cursor.h"

bool Cursor::Intersect(Alterable* alterable, float offsetX, float offsetY, GLFWwindow* window)
{
	if (getMousePosition(window).x > alterable->globalPosition.x& getMousePosition(window).x < alterable->globalPosition.x + offsetX)
	{
		if (getMousePosition(window).y > alterable->globalPosition.y& getMousePosition(window).y < alterable->globalPosition.y + offsetY)
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
	if (getMousePosition(window).x > ui->globalPosition.x& getMousePosition(window).x < ui->globalPosition.x + ui->size.x)
	{
		if (getMousePosition(window).y > ui->globalPosition.y& getMousePosition(window).y < ui->globalPosition.y + ui->size.y)
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
