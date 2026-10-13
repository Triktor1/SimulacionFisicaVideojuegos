#include "P1S_Scene.h"

void P1S_Scene::init() {
	particles.push_back(new Particle(Vector3D(-10, 0, 0), Vector3D(-4, 0, 0), Vector3D(4, 0, 0), 1));
	//particles.push_back(new Projectile(Vector3D(-10, 40, 0), Vector3D(4, 0, 0), Vector3D(250, 0, 0), Vector3D(4, 0, 0)));
}

void P1S_Scene::update(double dt) {
	for (auto& p : particles) {
		p->verlet(dt);
	}
}

void P1S_Scene::cleanup() {
	for (auto& r : renderItems) {
		if (r != nullptr) {
			r->release();
			r = nullptr;
		}
	}
	for (auto& t : transforms) {
		if (t != nullptr) {
			delete t;
			t = nullptr;
		}
	}
	for (auto& p : particles) {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
	}
}