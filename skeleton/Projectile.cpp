#include "Projectile.h"
Projectile::Projectile(Vector3D pos, Vector3D velSim, Vector3D velReal, Vector3D ac, float r, Vector3D gravity, float mass, Vector4 color, float d)
	: Particle(pos, velSim, ac, r, color, d), velReal(vel), gravityReal(gravity), massReal(mass)
{
	recalculateValues(); //Para devolver la velocidad, masa y gravedad a los valores simulados
}

void Projectile::recalculateValues() {
	//Cálculo de masa
	mass = massReal * pow(velReal.magnitude() / vel.magnitude(), 2);

	//Cálculo de gravedad
	gravity = gravityReal * pow(vel.magnitude() / velReal.magnitude() , 2);
}