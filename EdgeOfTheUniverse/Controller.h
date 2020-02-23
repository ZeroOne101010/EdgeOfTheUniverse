#pragma once
#include "Mob.h"
#include "glb.h"
class World;
using namespace glm;
class Controller
{
public:
	Controller();
	Controller(Entity* target);
	void setTarget(Entity* target);
	void UpdateController(World* world);
	Entity* target;
	vec2 Camera = vec2(0, 0);
	vec2 camVelosity;
	vec2 zeroCamera;
private:
	void Controll();
	void Interpol(float k);
};

