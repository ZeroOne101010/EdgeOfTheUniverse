#pragma once
#include "VAO.h"
class Shape : public VAO
{
public:
	Shape(VBO modelVBO, IBO modelIBO, VBO textureUV);
private:

protected:
	void setDrawParams() override;
};

