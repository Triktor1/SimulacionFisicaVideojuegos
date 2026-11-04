#pragma once
#include "Vector3D.h"

class Particle;
class ForceGenerator
{
public:
	virtual void updateForce(Particle* p, double dt) = 0;

	bool getActive() const { return active; };
	void setActive(bool a) { active = a; };
protected:
	bool active = true;
};

