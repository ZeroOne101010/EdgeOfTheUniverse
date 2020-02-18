#pragma once
#include "RandomCoor.h"
#include <glm/glm.hpp>

class PerlinNoise
{
public:
	static float lerp(float t, float a, float b);
	static float getPerlinNoise(float posX, float posZ, int offsetX, int offsetZ, RandomCoor* rand);
	static float getPerlinNoise2DWithCurve(float posX, float posY, int offsetX, int offsetZ, float T, float kPos, float kOffset, int countNoises, RandomCoor rand);
	static float smoothstep(float edge0, float edge1, float x);
	static float clamp(float x, float lowerlimit, float upperlimit);
};

