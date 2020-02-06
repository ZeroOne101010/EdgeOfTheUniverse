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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "initialization.h"

class VAO
{
public:
	GLuint indexVAO;
	
	VBO modelVBO;
	IBO modelIBO;
	GLuint localPosIndex;
	GLuint worldPosIndex;
	glm::vec2 position;
	glm::vec2 originPos;
	std::vector<VBO> vbo;
	Shader* shader = new DefaultShader();

	VAO(VBO modelVBO, IBO modelIBO);
	VAO(Shader* shader, VBO modelVBO, IBO modelIBO);
	~VAO();
	void setColor(GLfloat R, GLfloat G, GLfloat B, GLfloat A);
	
	void updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw);

	void draw();
private:
 	void setCoords();
};

