#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "VBO.h"
#include "IBO.h"
#include <fstream>
#include <sstream>
#include <vector>

class VAO;

class Shader
{
public:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	const GLchar* pathVertex;
	const GLchar* pathFragment;
	Shader();
	Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
	~Shader();
	void setShaderFromSource(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource); // k = n / (const / 4) * 0.5    k = (2 / const) * n
	void setShader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);
	void VerifySuccess(GLuint shader, std::string error);
	void VerifySuccess(GLuint program);
	void linkToVAO(VAO* vao);
	void updateData(VAO* vao, GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw);
	virtual void cloneShader() 
	{

	}
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

