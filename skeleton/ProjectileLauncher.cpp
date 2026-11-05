#include "ProjectileLauncher.h"
#include "Projectile.h"
#include "GravityForceGenerator.h"
#include <iostream>

//Se crea por defecto con gravedad nula
ProjectileLauncher::ProjectileLauncher() {
	gravityForce = new GravityForceGenerator(Vector3D());
}

//Para darle un valor distinto de gravedad al generador de gravedad
void ProjectileLauncher::setGravity(Vector3D g) {
	gravityForce->setGravity(g);
}

//Cada vez que se llama a este método se añade un proyectil nuevo con los parámetros que le des y se le añade gravedad
//Usando el mismo generador para todos los proyectiles
Projectile* ProjectileLauncher::shoot(Vector3D pos, Vector3D velSim, Vector3D velReal, float r, Vector3D gravityReal, float mass, Vector4 color, float d) {
	projectiles.push_back(new Projectile(pos, velSim, velReal, r, gravityReal, mass, color, d));
	projectiles.back()->addForceGenerator(gravityForce);
	return projectiles.back();
}

//Se integran todos los proyectiles
void ProjectileLauncher::update(float dt) {
	for (Projectile* p : projectiles) {
		if (p) {
			p->verlet(dt);
			p->setLifeTime(p->getLifeTime() - dt * 1000);
			if (p->getLifeTime() <= 0) {
				p->setVisible(false);
			}
		}
	}
}

ProjectileLauncher::~ProjectileLauncher() {
	if (gravityForce) {
		delete gravityForce;
		gravityForce = nullptr;
	}
	for (auto& p : projectiles) {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
	}
}