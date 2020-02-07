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

	glm::mat4 rotationMatrix;

	GLuint localPosIndex;
	GLuint worldPosIndex;
	GLuint rotationMatrixIndex;
	GLuint colorIndex;

	glm::vec2 position;
	glm::vec2 originPos;
	glm::vec4 color;
	std::vector<VBO> vbo;
	Shader* shader = new DefaultShader();

	VAO(VBO modelVBO, IBO modelIBO);
	VAO(Shader* shader, VBO modelVBO, IBO modelIBO);
	~VAO();
	void setColor();
	
	void updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw);

	void draw();
private:
 	void setCoords();
};

