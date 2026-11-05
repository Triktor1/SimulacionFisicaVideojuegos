#include "Particle.h"
#include "Emisor.h"
#include "ForceGenerator.h"
#include <iostream>

Particle::Particle(Vector3D pos, Vector3D vel, float r, Vector4 color, float d, float mass)
	: vel(vel), damping(d), antPos(pos), mass(mass), scale(r), iniScale(r), color(color) {
	pose = physx::PxTransform(pos);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pose, color);
	renderItem->scale = getScale();
	w = 1 / mass;
}

Particle::~Particle() {
	if (renderItem != nullptr) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::euler(double t) {
	updateForces(t);
	Vector3D ac = forceAcc * w;
	pose.p += vel * t;
	vel += ac * t;
	vel *= pow(damping, t);
}

void Particle::semiImplicitEuler(double t) {
	updateForces(t);
	Vector3D ac = forceAcc * w;
	vel = (vel + ac * t) * pow(damping, t);
	pose.p += vel * t;
}

void Particle::verlet(double t) {
	if (firstIntegration) {
		semiImplicitEuler(t);
		firstIntegration = false;
	}
	else {
		updateForces(t);
		Vector3D ac = forceAcc * w;
		Vector3D ant = pose.p;
		pose.p = 2 * pose.p - antPos + ac * pow(t, 2);
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

void Particle::setColor(Vector4 c) {
	Vector4 col = c;
	Emissor* e = getActualEmissor();
	if (e && e->getInterpolatingColors()) {
		col = e->getActualInterpolatedColor(lifeTime / originalLifeTime);
	}
	renderItem->color = col;
	color = col;
}

void Particle::setVisible(bool v) {
	isAlive = v;
	if (v) {
		firstIntegration = true;
		antPos = pose.p;
		forceAcc = Vector3D();
		renderItem->scale = getScale();
	}
	else {
		renderItem->scale = 0.0f;
		setActualEmissor(nullptr);
	}
}

void Particle::updateForces(double dt) {
	clearForces();
	for (ForceGenerator* f : forceGenerators) {
		f->updateForce(this, dt);
	}
}

void Particle::clearForces() {
	forceAcc = Vector3D();
}