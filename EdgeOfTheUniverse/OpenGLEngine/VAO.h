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
#include "Texture.h"
#include "RenderWindow.h"
#include "IDraw.h"
#include "Alterable.h"

class VAO : public IDraw, public Alterable
{
public:

	GLuint indexVAO;
	VBO modelVBO;
	IBO* modelIBO;
	VBO textureUV;

	glm::mat4 rotation;
	glm::vec2 Size;
	glm::vec4 Color = glm::vec4(255, 255, 255, 255);

	std::vector<VBO> vbo;
	Shader* shader;
	Texture* texture;
	FloatRect textureRect = FloatRect(0, 0, 1, 1);

	VAO(GLuint VAOBufferID, Shader* shader, Texture* texture, IBO* modelIBO);
	//���������� �� ���������, �� ������ ��������. ��� :} (�� �������, ���� ��� �����)

	static GLuint createVAOBuffer();
	void setTexture(Texture texture);
	void setColor();

	static void bindVBO(VBO* vbo, GLuint indexVAO, GLuint indexAttribute);
	static void bindVBOIBO(VBO* vbo, IBO* ibo, GLuint indexVAO, GLuint indexAttribute);

	void draw();
	virtual void draw(Renderer* renderer, Alterable alters) override;
private:
 	void setCoords();
	void setSize();
	glm::vec2 drawPosition;
	glm::vec2 drawOrigin;
	glm::vec2 drawRelSize = glm::vec2(1, 1);
	glm::vec2 drawSize;
	GLfloat drawAngle = 0;

	GLuint localPosIndex;
	GLuint worldPosIndex;
	GLuint angleIndex;
	GLuint colorIndex;
	GLuint relSizeIndex;
	GLuint correctSizeIndex;
	GLuint sizeIndex;

	GLuint coordsUVIndex;
	GLuint textureSamplerIndex;

	glm::vec2 position;
	glm::vec2 origin;
	glm::vec2 relSize = glm::vec2(1, 1);
	glm::vec2 correctSize = glm::vec2(1.0f / (float)RenderWindow::width, 1.0f / (float)RenderWindow::height);
protected:
	virtual void setDrawParams();


};

