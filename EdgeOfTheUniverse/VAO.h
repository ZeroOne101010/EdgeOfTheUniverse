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
#include "Texture.h"
#include "RenderWindow.h"
#include "IDraw.h"
#include "Alterable.h"

class VAO : public IDraw, public Alterable
{
public:
	GLuint indexVAO;
	VBO modelVBO;
	IBO modelIBO;
	VBO textureUV;

	glm::mat4 rotation;
	glm::vec2 Size;
	glm::vec4 Color;

	std::vector<VBO> vbo;
	Shader* shader = new DefaultShader();
	Texture* texture = new Texture("Resources/Textures/DefaultTexture3.png");
	FloatRect textureRect = FloatRect(0, 0, 1, 1);

	VAO(VBO modelVBO, IBO modelIBO, VBO textureUV);
	VAO(Shader* shader, VBO modelVBO, IBO modelIBO, VBO textureUV);
	~VAO();

	void setTexture(Texture texture);

	void setTextureRect(FloatRect rect);

	void setColor();
	
	void updateData(GLuint IDAttributeInArray, GLsizeiptr sizeData, GLfloat* data, GLenum typeDraw);

	void draw();
	virtual void draw(Renderer* renderer, Alterable alters) override;
private:
 	void setCoords();
	void setSize();
	glm::vec2 drawPosition;
	glm::vec2 drawOrigin;
	glm::vec2 drawRelSize = glm::vec2(1, 1);
	glm::vec2 drawSize;
	GLfloat drawAngle;

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
	glm::vec2 correctSize = glm::vec2(RenderWindow::sizeConst / (float)RenderWindow::width, RenderWindow::sizeConst / (float)RenderWindow::height);
protected:
	virtual void setDrawParams();


};

