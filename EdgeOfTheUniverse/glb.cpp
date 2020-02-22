#include "glb.h"

float glb::Lerp(float a, float b, float k)
{
	return a + (b - a) * k;
}

glm::vec2 glb::normalize(glm::vec2 kek)
{
	float vecLong = (kek.x * kek.x) + (kek.y * kek.y);
	return kek / vecLong;
}
