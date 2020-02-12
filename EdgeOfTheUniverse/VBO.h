#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
class VBO
{
public:
	GLuint index;
	GLfloat* data;

	VBO();
	VBO(GLsizeiptr size, GLfloat* data, GLenum typeDraw);
	~VBO();
	void UpdateData(GLsizeiptr size, GLfloat* data, GLenum typeDraw);

};

