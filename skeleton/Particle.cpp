#include "Particle.h"
#include <iostream>

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D ac, float r, Vector4 color, float d, Vector3D gravity, float mass)
	: vel(vel), ac(ac), damping(d), antPos(pos), mass(mass), gravity(gravity), scale(r), iniScale(r), color(color) {
	pose = physx::PxTransform(pos);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(scale)), &pose, color);
}

Particle::~Particle() {
	if (renderItem != nullptr) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::euler(double t) {
	pose.p += vel * t;
	vel += (ac + gravity) * t;
	vel *= pow(damping, t);
}

void Particle::semiImplicitEuler(double t) {
	vel = (vel + (ac + gravity) * t) * pow(damping, t);
	pose.p += vel * t;
}

void Particle::verlet(double t) {
	if (firstIntegration) {
		semiImplicitEuler(t);
		firstIntegration = false;
	}
	else {
		Vector3D ant = pose.p;
		pose.p = 2 * pose.p - antPos + (ac + gravity) * pow(t, 2);
		antPos = ant;
	}
}

void Particle::setShape(physx::PxShape* s) {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
	renderItem = new RenderItem(s, &pose, color);
}

void Particle::setVisible(bool v) {
	if (v && !renderItem) {
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(getScale()));
		renderItem = new RenderItem(shape, &pose, color);
		firstIntegration = true;
		isAlive = true;
	}
	else if (!v && renderItem) {
		renderItem->release();
		renderItem = nullptr;
		isAlive = false;
	}
}