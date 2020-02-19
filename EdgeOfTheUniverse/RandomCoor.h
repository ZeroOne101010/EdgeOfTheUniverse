#pragma once
#include <cstdlib>

class RandomCoor
{
public:
	char** numberMap;
	int sizeNumberMap;
	float seed;

	RandomCoor(int sizeNumberMap, int seed);
	bool getProbably(int posX, int posY, int maxSize, int probably);
	float next(int posX, int posY, float min, float max);
	static float next(float min, float max);

};

