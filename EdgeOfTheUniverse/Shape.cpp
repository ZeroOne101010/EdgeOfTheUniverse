#include "Shape.h"

Shape::Shape(VBO modelVBO, IBO modelIBO, VBO textureUV) : VAO(modelVBO, modelIBO, textureUV)
{
}

void Shape::setDrawParams()
{
	VAO::setDrawParams();
}
