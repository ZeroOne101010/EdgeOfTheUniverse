#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "VBO.h"
#include <vector>
#include "IBO.h"
#include "DefaultShader.h"

class VAO
{
public:
	GLuint indexVAO;
	
	VBO modelVBO;
	IBO modelIBO;

	std::vector<VBO> vbo;

	Shader shader = DefaultShader();

	VAO(VBO modelVBO, IBO modelIBO);
	VAO(Shader shader, VBO modelVBO, IBO modelIBO);

	void updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw);

	void draw();
};

