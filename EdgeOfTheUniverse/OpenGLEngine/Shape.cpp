#include "Shape.h"

Shape::Shape(GLuint VAOBufferID, Shader* shader, Texture* texture, IBO* modelIBO) : VAO(VAOBufferID, shader, texture, modelIBO)
{
}

void Shape::setDrawParams()
{
	VAO::setDrawParams();
}
