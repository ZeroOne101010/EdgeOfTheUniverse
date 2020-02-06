#pragma once
#include "Shader.h"

class DefaultShader : public Shader
{
public:
	DefaultShader();
	void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
};

