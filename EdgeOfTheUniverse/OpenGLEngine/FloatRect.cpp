#include "FloatRect.h"

FloatRect::FloatRect()
{
}

FloatRect::FloatRect(GLfloat positionX, GLfloat positionY, GLfloat sizeX, GLfloat sizeY)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

FloatRect::FloatRect(glm::vec2 position, GLfloat sizeX, GLfloat sizeY)
{
	this->positionX = position.x;
	this->positionY = position.y;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

FloatRect::FloatRect(GLfloat positionX, GLfloat positionY, glm::vec2 size)
{
	this->positionX = positionX;
	this->positionY = positionY;
	this->sizeX = size.x;
	this->sizeY = size.y;
}

FloatRect::FloatRect(glm::vec2 position, glm::vec2 size)
{
	this->positionX = position.x;
	this->positionY = position.y;
	this->sizeX = size.x;
	this->sizeY = size.y;
}

