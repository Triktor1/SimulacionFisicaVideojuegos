#include "WindForceGenerator.h"
#include "Particle.h"

WindForceGenerator::WindForceGenerator(Vector3D pos, Vector3D vel, float LX, float LY, float LZ, float k1, float k2)
	: pos(pos), vel(vel), LX(LX), LY(LY), LZ(LZ), k1(k1), k2(k2) {
}

void WindForceGenerator::updateForce(Particle* particle, double dt) {
	if (particle->getMass() <= 0)
		return;
	if (active && getAABB(particle->getPos())) {
		Vector3D relativeVelocity = vel - particle->getVel();
		Vector3D force = relativeVelocity * k1
			+ relativeVelocity * relativeVelocity.magnitude() * k2;
		particle->addForce(force);
	}
}

bool WindForceGenerator::getAABB(Vector3D other) const {
	return other.x >= pos.x - (LX / 2) && other.x <= pos.x + (LX / 2) &&
		other.y >= pos.y - (LY / 2) && other.y <= pos.y + (LY / 2) &&
		other.z >= pos.z - (LZ / 2) && other.z <= pos.z + (LZ / 2);
}