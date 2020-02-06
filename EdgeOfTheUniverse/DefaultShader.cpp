#include "DefaultShader.h"

	DefaultShader::DefaultShader() : Shader()
	{
		const GLchar* fragmentShaderSource =
			"#version 330 core \n"
			"out vec4 color; \n"
			"uniform vec4 Color;\n"
			"void main() \n"
			"{ \n"
			"color = Color; \n"
			"} \n";

		const GLchar* vertexShaderSource =
			"#version 330 core \n"
			"layout (location = 0) in vec3 position; \n"
			"void main() \n"
			"{ \n"
			"gl_Position = vec4(position, 1.0); \n"
			"} \n";

		setShaderSource(vertexShaderSource, fragmentShaderSource);
		useShaderProgram();
		GLuint index = glGetUniformLocation(shaderProgram, "Color");
		glUniform4f(index, 0.5f, 1, 1, 1);
	}