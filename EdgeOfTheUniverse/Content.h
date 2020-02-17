#pragma once
#include "OpenGLEngine/DefaultShader.h"
#include "OpenGLEngine/Texture.h"
#include "OpenGLEngine/VBO.h"
#include "OpenGLEngine/IBO.h"

class Content
{
public:

	//���������� ����������
	static VBO::Attribute defaultModelAttribute;
	static VBO::Attribute defaultTextureUVAttribute;

	//���������� VAO
	static GLuint indexRectangleShape;

	//���������� IBO
	static IBO* rectangleShapeIBO;

	//���������� VBO
	static VBO* rectangleShapeVBO;
	static VBO* rectangleTextureUVVBO;


	//���������� �������� (���� ������ ����)
	static DefaultShader* defaultShader;

	//���������� �������
	static Texture* defaultTexture;
	static Texture* spriteList_Grass;


	static void load();

};

