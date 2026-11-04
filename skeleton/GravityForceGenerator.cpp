#include "GravityForceGenerator.h"
#include "Particle.h"

GravityForceGenerator::GravityForceGenerator(Vector3D gravity) :
	gravity(gravity) {
}

void GravityForceGenerator::updateForce(Particle* particle, double dt) {
	if (particle->getMass() <= 0)
		return;
	if (active) {
		Vector3D force = gravity * particle->getMass();
		particle->addForce(force);
	}
}

void GravityForceGenerator::setGravity(Vector3D g) {
	gravity = g;
}