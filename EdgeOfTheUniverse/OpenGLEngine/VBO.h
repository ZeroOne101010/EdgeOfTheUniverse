#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
class Shader;

class VBO
{
public:
	GLuint index;
	GLfloat* data;

	struct Attribute
	{
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* pointer;
	};

	Attribute attribute;
	void setAttribute(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

	VBO();
	VBO(GLsizeiptr size, GLfloat* data, GLenum typeDraw, Attribute attribute);
	VBO(GLsizeiptr size, GLfloat* data, GLenum typeDraw, GLint sizeAttribute, GLenum typeAttribute, GLboolean normalizedAttribute, GLsizei strideAttribute, const void* pointerAttribute);
	~VBO();
	void UpdateData(GLsizeiptr size, GLfloat* data, GLenum typeDraw);


};

