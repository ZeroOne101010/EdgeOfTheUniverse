#pragma once
#include "OpenGLEngine/DefaultShader.h"
#include "LightingShader.h"
#include "OpenGLEngine/Texture.h"
#include "OpenGLEngine/VBO.h"
#include "OpenGLEngine/IBO.h"

class Content
{
public:

	//ќбъ€вление атрибуетов
	static VBO::Attribute defaultModelAttribute;
	static VBO::Attribute defaultTextureUVAttribute;

	//ќбъ€вление VAO
	static GLuint indexRectangleShape;

	//ќбъ€вление IBO
	static IBO* rectangleShapeIBO;

	//ќбъ€вление VBO
	static VBO* rectangleShapeVBO;
	static VBO* rectangleTextureUVVBO;


	//ќбъ€вление шейдеров
	static DefaultShader* defaultShader;
	static LightingShader* lightingShader;

	//ќбъ€вление текстур
	static Texture* defaultTexture;
	static Texture* spriteList_Grass;
	static Texture* spriteList_Dirt;


	static void load();

};

