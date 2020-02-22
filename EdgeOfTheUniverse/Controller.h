#pragma once
#include "Mob.h"
#include "glb.h"
class World;
using namespace glm;
class Controller
{
public:
	Controller();
	Controller(Mob* target);
	void setTarget(Mob* target);
	void UpdateController(World* world);
	Mob* target;
	vec2 Camera = vec2(0, 0);
	vec2 camVelosity;
	vec2 zeroCamera;
private:
	void Controll();
	void Interpol(float k);
};

