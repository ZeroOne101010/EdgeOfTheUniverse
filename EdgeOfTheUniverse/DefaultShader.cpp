#include "DefaultShader.h"

	DefaultShader::DefaultShader() : Shader("Resources/Shaders/DefaultShader.vert", "Resources/Shaders/DefaultShader.frag")
	{
		GLuint index = glGetUniformLocation(shaderProgram, "Color");

		useShaderProgram();
		glUniform4f(index, 0.5f, 1, 1, 1);
	}

	void DefaultShader::setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A)
	{
		GLuint index = glGetUniformLocation(shaderProgram, "Color");

		useShaderProgram();
		glUniform4f(index, R, G, B, A);
	}