#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector> 
class IBO
{
public:
	GLuint index;
	GLsizei size;
	
	IBO();
	IBO(GLsizeiptr size, GLuint* data, GLenum typeDraw);
	void UpdateIBO(GLsizeiptr size, GLuint* data, GLenum typeDraw);
};

