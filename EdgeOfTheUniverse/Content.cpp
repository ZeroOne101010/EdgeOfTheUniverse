#include "OpenGLEngine/VAO.h"
#include "Content.h"

//Инициализация атрибуетов
VBO::Attribute Content::defaultModelAttribute;
VBO::Attribute Content::defaultTextureUVAttribute;

//Иницилизация VAO
GLuint Content::indexRectangleShape;

//Иницилизация IBO
IBO* Content::rectangleShapeIBO;

//Иницилизация VBO
VBO* Content::rectangleShapeVBO;
VBO* Content::rectangleTextureUVVBO;


//Иницилизация шейдеров (Пока только один)
DefaultShader* Content::defaultShader;

//Иницилизация текстур
Texture* Content::defaultTexture;
Texture* Content::spriteList_Grass;

void Content::load()
{
	defaultModelAttribute.size = 3;
	defaultModelAttribute.type = GL_FLOAT;
	defaultModelAttribute.normalized = GL_FALSE;
	defaultModelAttribute.stride = sizeof(GLfloat) * 3;
	defaultModelAttribute.pointer = 0;

	defaultTextureUVAttribute.size = 2;
	defaultTextureUVAttribute.type = GL_FLOAT;
	defaultTextureUVAttribute.normalized = GL_FALSE;
	defaultTextureUVAttribute.stride = sizeof(GLfloat) * 2;
	defaultTextureUVAttribute.pointer = 0;

	//Вероятно, для инициализации буфера стоила загружать данные с файла, но время поджимает, так что фигушки
	GLfloat rectangleShapeVertices[] =
	{
		 0.0f,  0.0f, 0.0f,
		 0.5f,  0.0f, 0.0f,
		 0.5f,  -0.5f, 0.0f,
		 0.0f,  -0.5f, 0.0f,
	};

	GLuint rectangleShapeIndices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	GLfloat rectangleShapeCoordsUV[] =
	{
		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,
		 0.0f, 1.0f
	};

	defaultShader = new DefaultShader();

	rectangleShapeIBO = new IBO(sizeof(GLuint) * 6, rectangleShapeIndices, GL_STREAM_DRAW);

	rectangleShapeVBO = new VBO(sizeof(GLfloat) * 12, rectangleShapeVertices, GL_STREAM_DRAW, defaultModelAttribute);
	rectangleTextureUVVBO = new VBO(sizeof(GLfloat) * 12, rectangleShapeCoordsUV, GL_STREAM_DRAW, defaultTextureUVAttribute);

	////////НЕ ЗАБЫТЬ СДЕЛАТЬ ПУТЬ, ОТНОСИТЕЛЬНО ИСПОЛНИТЕЛЬНОГО ФАЙЛА!!!
	defaultTexture = new Texture();
	spriteList_Grass = new Texture("E:\\EdgeOfTheUniverse\\EdgeOfTheUniverse\\Resources\\Textures\\SpriteList_Grass.png");

	indexRectangleShape = VAO::createVAOBuffer();
	VAO::bindVBOIBO(rectangleShapeVBO, rectangleShapeIBO, indexRectangleShape, 0);
	VAO::bindVBO(rectangleTextureUVVBO, indexRectangleShape, 1);
}
