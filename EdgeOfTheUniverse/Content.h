#pragma once
#include "OpenGLEngine/DefaultShader.h"
#include "LightingShader.h"
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


	//���������� ��������
	static DefaultShader* defaultShader;
	static LightingShader* lightingShader;

	//���������� �������
	static Texture* defaultTexture;
	static Texture* spriteList_Grass;
	static Texture* spriteList_Dirt;


	static void load();

};

