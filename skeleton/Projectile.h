#pragma once
#include "Particle.h"
class Projectile :
    public Particle
{
public:
	Projectile(Vector3D pos, Vector3D velSim, Vector3D velReal, float r = 1.0f, Vector3D gravityReal = Vector3D(0, -9.81, 0), float mass = 5.0f, Vector4 color = Vector4(1, 1, 0, 1), float d = 1.0f);

	void setVelReal(Vector3D v) { velReal = v; }

	Vector3D getVelReal() const { return velReal; }

private:
	Vector3D velReal;
	Vector3D gravityReal;
	float massReal;
	void recalculateValues();
};

