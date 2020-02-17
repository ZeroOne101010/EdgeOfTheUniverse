#pragma once
#include <iostream>
#include <glm/glm.hpp>
class ByteHelper
{
public:
	static int setValue2To10(int* code, int size, int value2);
	static int set256To10(unsigned char* code, int size);
	static int getSizeCode(int value1, int value2);
	static int* set10ToValue(int value, float res, int& size);
	static unsigned char* set10To256(int value, int& size);
	static float distance(glm::vec2 vec1, glm::vec2 vec2);
};

