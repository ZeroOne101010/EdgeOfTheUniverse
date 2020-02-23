#include "Mob.h"

float Mob::G = 0.15f;

Mob::Mob()
{
}

void Mob::A(float speed)
{
	velocity = glm::vec2(speed - this->moveSpeed - flySpeed, velocity.y);
}

void Mob::D(float speed)
{
	velocity = glm::vec2(speed + this->moveSpeed + flySpeed, velocity.y);
}

void Mob::W(float hightJump)
{
	velocity = glm::vec2(velocity.x, hightJump - flySpeed);
}

void Mob::S(float downSpeed)
{
	velocity = glm::vec2(velocity.x, downSpeed + flySpeed);
}

void Mob::update()
{
	velocity.y += G;
	Position += velocity;
	IntersectedEntity::update();
}

