#include "Shape.h"

Shape::Shape(GLuint VAOBufferID, Shader* shader,TBO* texture, IBO* modelIBO) : VAO(VAOBufferID, shader, texture, modelIBO)
{
}

void Shape::setDrawParams()
{
	VAO::setDrawParams();
}
