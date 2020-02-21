#pragma once
#include "VAO.h"
#include "../TBO.h"
class Shape : public VAO
{
public:
	Shape(GLuint VAOBufferID, Shader* shader, TBO* texture, IBO* modelIBO);
private:

protected:
	void setDrawParams() override;
};

