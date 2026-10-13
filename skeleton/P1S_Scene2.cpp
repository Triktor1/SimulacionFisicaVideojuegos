#include "P1S_Scene2.h"

void P1S_Scene2::init() {
	//projectiles.push_back(new Particle(Vector3D(-10, 0, 0), Vector3D(-4, 0, 0), Vector3D(4, 0, 0), 1));
}

void P1S_Scene2::update(double dt) {
	for (auto& p : projectiles) {
		p->verlet(dt);
	}
}

void P1S_Scene2::cleanup() {
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
	for (auto& p : projectiles) {
		if (p != nullptr) {
			delete p;
			p = nullptr;
		}
	}

}

void P1S_Scene2::keyPress(unsigned char key, const physx::PxTransform& camera) {
	Vector3D dir = Vector3D(camera.q.rotate(physx::PxVec3(0.0f, 0.0f, -1.0f)));
	switch (key) {
	case 'p': case 'P':
		projectiles.push_back(new Projectile(camera.p, dir * 10, dir * 250));
		break;
	case 'o': case 'O':
		projectiles.push_back(new Projectile(camera.p, dir * 72, dir * 1800, Vector3D(0,0,0), 1, Vector3D(0, -9.81, 0), 5, Vector4(0, 1, 0, 1)));
		break;
	case 'i': case 'I':
		projectiles.push_back(new Projectile(camera.p, dir * 120, dir * 30000, Vector3D(0, 0, 0), 1, Vector3D(0, -9.81, 0), 5, Vector4(1, 0, 0, 1)));
		projectiles.back()->setShape(CreateShape(physx::PxBoxGeometry(1,1,1)));
		break;
	}

}
