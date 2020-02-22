#pragma once
#include "IntersectedEntity.h"
class Mob : public IntersectedEntity
{
public:

	static float G;

	Mob();
	virtual void A(float speed);
	virtual void D(float speed);
	virtual void W(float hightJump);
	virtual void S(float downSpeed);

	virtual void update() override;
	float moveSpeed;
	float flySpeed;
	float Af;
	float Df;
	float Wf;
	float Sf;
};

