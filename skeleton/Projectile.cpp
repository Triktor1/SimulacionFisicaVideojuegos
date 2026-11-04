#include "Projectile.h"
Projectile::Projectile(Vector3D pos, Vector3D velSim, Vector3D velReal, float r, Vector3D gravityReal, float mass, Vector4 color, float d)
	: Particle(pos, velSim, r, color, d), velReal(velReal), massReal(mass), gravityReal(gravityReal)
{
	recalculateValues(); //Para devolver la velocidad, masa y gravedad a los valores simulados
	setLifeTime(100000);
}

void Projectile::recalculateValues() {
	//Cálculo de masa
	float velMag = vel.magnitude();
	if (velMag == 0) velMag = 0.0001f;
	mass = massReal * pow(velReal.magnitude() / velMag, 2);
	w = 1 / mass;
}