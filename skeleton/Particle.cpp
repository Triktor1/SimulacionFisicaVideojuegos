#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D ac, float r, Vector4 color, float d, Vector3D gravity, float mass)
: vel(vel), ac(ac), damping(d), antPos(pos), mass(mass), gravity(gravity){
	pose = physx::PxTransform(pos);
	shape = CreateShape(physx::PxSphereGeometry(r));
	renderItem = new RenderItem(shape, &pose, color);
}

Particle::~Particle() {
	if (renderItem != nullptr) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::euler(double t) {
	pose.p += vel * t;
	vel += (ac+gravity) * t;
	vel *= pow(damping, t);
}

void Particle::semiImplicitEuler(double t) {
	vel = (vel + (ac+gravity) * t) * pow(damping, t);
	pose.p += vel * t;
}

void Particle::verlet(double t) {
	if (firstIntegration) {
		semiImplicitEuler(t);
		firstIntegration = false;
	}
	else {
		Vector3D ant = pose.p;
		pose.p = 2 * pose.p - antPos + (ac+gravity) * pow(t, 2);
		antPos = ant;
	}
}

void Particle::setShape(physx::PxShape* s) {
	if (shape)
		shape->release();

	shape = s;
	if (shape)
		shape->acquireReference();

	if (renderItem->shape)
		renderItem->shape->release();

	renderItem->shape = s;
	if (renderItem->shape)
		renderItem->shape->acquireReference();
}