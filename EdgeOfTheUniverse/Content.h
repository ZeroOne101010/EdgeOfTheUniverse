#pragma once
#include "OpenGLEngine/DefaultShader.h"
#include "LightingShader.h"
#include "OpenGLEngine/Texture.h"
#include "OpenGLEngine/VBO.h"
#include "OpenGLEngine/IBO.h"
#include "TBO.h"

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
	static TBO* defaultTexture;
	static TBO* spriteList_Grass;
	static TBO* spriteList_Dirt;
	static TBO* sprite_AmnisItem;

	static void load();

};

