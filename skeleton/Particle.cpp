#include "Particle.h"

Particle::Particle(Vector3D pos, Vector3D vel, Vector3D ac, float d) 
	: vel(vel), ac(ac), damping(d) {
	pose = physx::PxTransform(pos);
	shape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(shape, &pose, Vector4(1.0f, 1.0f, 0.0f, 1.0f));
}

Particle::~Particle() {
	if (renderItem != nullptr) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double t) {
	pose.p += vel * t;
	vel += ac * t;
	vel *= pow(damping, t);
}
