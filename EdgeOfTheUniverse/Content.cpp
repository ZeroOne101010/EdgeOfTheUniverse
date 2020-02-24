#include "OpenGLEngine/VAO.h"
#include "ConvertRegionData.h"
#include "Content.h"

//������������� ����������
VBO::Attribute Content::defaultModelAttribute;
VBO::Attribute Content::defaultTextureUVAttribute;

//������������ VAO
GLuint Content::indexRectangleShape;

//������������ IBO
IBO* Content::rectangleShapeIBO;

//������������ VBO
VBO* Content::rectangleShapeVBO;
VBO* Content::rectangleTextureUVVBO;


//������������ ��������
DefaultShader* Content::defaultShader;
LightingShader* Content::lightingShader;

//������������ �������
TBO* Content::defaultTexture;
TBO* Content::spriteList_Grass;
TBO* Content::spriteList_Dirt;
TBO* Content::sprite_AmnisItem;
TBO* Content::SpriteList_Tools;
TBO* Content::SpriteList_Stone;

const GLchar* Content::fileName(std::string localPath)
{
	std::cout << ConvertRegionData::getPathGLChar(localPath) << std::endl;
	return ConvertRegionData::getPathGLChar(localPath);
}

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
	lightingShader = new LightingShader();

	rectangleShapeIBO = new IBO(sizeof(GLuint) * 6, rectangleShapeIndices, GL_STREAM_DRAW);

	rectangleShapeVBO = new VBO(sizeof(GLfloat) * 12, rectangleShapeVertices, GL_STREAM_DRAW, defaultModelAttribute);
	rectangleTextureUVVBO = new VBO(sizeof(GLfloat) * 12, rectangleShapeCoordsUV, GL_STREAM_DRAW, defaultTextureUVAttribute);
	defaultTexture = new TBO();
	spriteList_Grass = new TBO(fileName("Resources\\Textures\\SpriteList_Grass.png"));
	spriteList_Dirt = new TBO(fileName("Resources\\Textures\\SpriteList_Dirt.png"));
	sprite_AmnisItem = new TBO(fileName("Resources\\Textures\\Items\\AmnisLogo.png"));
	SpriteList_Tools = new TBO(fileName("Resources\\Textures\\Items\\SpriteList_Tools.png"));
	SpriteList_Stone = new TBO(fileName("Resources\\Textures\\SpriteList_Stone.png"));
	indexRectangleShape = VAO::createVAOBuffer();
	VAO::bindVBOIBO(rectangleShapeVBO, rectangleShapeIBO, indexRectangleShape, 0);
	VAO::bindVBO(rectangleTextureUVVBO, indexRectangleShape, 1);
}
