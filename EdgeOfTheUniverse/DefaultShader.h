#pragma once
#include "Shader.h"

class DefaultShader : public Shader
{
public:

	GLuint localPosIndex;
	GLuint worldPosIndex;
	GLuint angleIndex;
	GLuint colorIndex;
	GLuint relSizeIndex;
	GLuint correctSizeIndex;
	GLuint sizeIndex;

	GLuint coordsUVIndex;
	GLuint textureSamplerIndex;

	DefaultShader(const GLchar* pathVertex = "Resources/Shaders/DefaultShader.vert", const GLchar* pathFragment = "Resources/Shaders/DefaultShader.frag");
	void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
};

