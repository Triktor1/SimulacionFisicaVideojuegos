#pragma once
#include "Particle.h"
class Projectile :
    public Particle
{
public:
	Projectile(Vector3D pos, Vector3D velSim, Vector3D velReal, Vector3D ac = Vector3D(), float r = 1.0f, Vector3D gravity = Vector3D(0, -9.81, 0), float mass = 5.0f, Vector4 color = Vector4(1, 1, 0, 1), float d = 1.0f);

private:
	Vector3D velReal;
	Vector3D gravityReal;
	float massReal;

	void recalculateValues();
	void changeMass();
};

