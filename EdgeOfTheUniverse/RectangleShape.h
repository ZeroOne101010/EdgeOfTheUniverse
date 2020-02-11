#pragma once
#include "Shape.h"
class RectangleShape : public Shape
{
public:
	static GLfloat RectangleShapeVertices[];
	static GLuint RectangleShapeIndices[];
	static GLfloat RectangleShapeCoordsUV[];
	RectangleShape(GLfloat sizeX, GLfloat sizeY);
	RectangleShape(glm::vec2 size);
private:
	void setDrawParams() override;
	void setRectangleSize();
};

