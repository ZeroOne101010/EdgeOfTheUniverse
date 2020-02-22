#pragma once
#include "Mob.h"
class FreeCamera : public Mob
{
public:
	FreeCamera();

	virtual Entity* getNewEntity() override;
	virtual void A(float speed) override;
	virtual void D(float speed) override;
	virtual void W(float speed) override;
	virtual void S(float speed) override;
};

