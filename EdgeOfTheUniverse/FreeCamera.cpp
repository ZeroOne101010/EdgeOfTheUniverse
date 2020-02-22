#include "FreeCamera.h"

FreeCamera::FreeCamera()
{
}

Entity* FreeCamera::getNewEntity()
{
	return new FreeCamera;
}

void FreeCamera::A(float speed)
{
	Mob::A(speed);
}

void FreeCamera::D(float speed)
{
	Mob::D(speed);
}

void FreeCamera::W(float speed)
{
	//Mob::W(hightJump);
	Position += glm::vec2(0, speed);
}

void FreeCamera::S(float speed)
{
	Position += glm::vec2(0, speed);
	//Mob::S(downSpeed);
}
