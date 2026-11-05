#include "ExplosionForceGenerator.h"
#include "Particle.h"

ExplosionForceGenerator::ExplosionForceGenerator(Vector3D pos, float T, float K, float expansionVel)
	: pos(pos), R(0), T(T), K(K), expansionVel(expansionVel), tAct(0) {
}

void ExplosionForceGenerator::updateForce(Particle* particle, double dt) {
	//Si la masa es negativa o nula no se hacen cálculos
	if (particle->getMass() <= 0)
		return;

	Vector3D partPos = particle->getPos();
	float r = sqrt(pow(partPos.x - pos.x, 2) + pow(partPos.y - pos.y, 2) + pow(partPos.z - pos.z, 2));

	R = expansionVel * tAct;

	if (active && r < R) {
		Vector3D force = Vector3D(partPos.x - pos.x, partPos.y - pos.y, partPos.z - pos.z) * (K / pow(r, 2)) * exp(-tAct / T);
		particle->addForce(force);
	}
}

void ExplosionForceGenerator::updateTime(double dt) {
	//Sumamos el tiempo
	tAct += dt * 1000;

	//Si t llega a 4T es tan insignificante que se desactiva
	if (tAct >= T * 4) 
		setActive(false);
}

void ExplosionForceGenerator::setActive(bool a) {
	active = a;
	if (a) {
		tAct = 0;
	}
}