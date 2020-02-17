#pragma once
#include "VAO.h"
class Shape : public VAO
{
public:
	Shape(GLuint VAOBufferID, Shader* shader, Texture* texture, IBO* modelIBO);
private:

protected:
	void setDrawParams() override;
};

