#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "VBO.h"
#include "IBO.h"
#include <vector>

class VAO;

class Shader
{
public:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	Shader();
	Shader(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);
	void setShaderSource(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);

	void linkToVAO(VAO* vao);
	void updateData(VAO* vao, GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw);

	void useShaderProgram();

	struct Attribute
	{
		VBO vbo;
		GLuint index;
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;
	};

	std::vector<Attribute> attribute;
	void addAttribute(VBO vbo, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

};

