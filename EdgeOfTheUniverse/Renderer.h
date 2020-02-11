#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Alterable.h"
//#include "RectangleShape.h"
class IDraw;
class Renderer
{
public:
	void draw(IDraw* obj, Alterable alters = Alterable::Default);
};

