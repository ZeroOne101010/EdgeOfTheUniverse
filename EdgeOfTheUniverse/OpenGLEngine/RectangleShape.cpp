#include "../Content.h"
#include "RectangleShape.h"
//RectangleShape::RectangleShape(GLfloat sizeX, GLfloat sizeY) : Shape(VBO(sizeof(GLfloat) * 12, RectangleShapeVertices, GL_STREAM_DRAW), IBO(sizeof(GLuint) * 6, RectangleShapeIndices, GL_STREAM_DRAW), VBO(sizeof(GLfloat) * 12, RectangleShapeCoordsUV, GL_STREAM_DRAW))
RectangleShape::RectangleShape(GLfloat sizeX, GLfloat sizeY) : Shape(Content::indexRectangleShape, Content::defaultShader, Content::defaultTexture, Content::rectangleShapeIBO)
{
	Size = glm::vec2(sizeX, sizeY);
}

RectangleShape::RectangleShape(glm::vec2 size) : Shape(Content::indexRectangleShape, Content::defaultShader, Content::defaultTexture, Content::rectangleShapeIBO)
{
	Size = size;
}

void RectangleShape::setDrawParams()
{
	Shape::setDrawParams();
}
