#include "P1S_Scene2.h"

void P1S_Scene2::init() {
	launcher.setGravity(Vector3D(0, -9.81, 0));
}

void P1S_Scene2::update(double dt) {
	launcher.update(dt);
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
}

void P1S_Scene2::keyPress(unsigned char key, const physx::PxTransform& camera) {
	Vector3D dir = Vector3D(camera.q.rotate(physx::PxVec3(0.0f, 0.0f, -1.0f)));
	switch (key) {
	case 'p': case 'P': {
		Projectile* projectile = launcher.shoot(camera.p + dir.normalize() * distanceFromCamera, dir * 10, dir * 250);
		projectile->setLifeTime(5000);
		break;
	}
	case 'o': case 'O': {
		Projectile* projectile = launcher.shoot(camera.p + dir.normalize() * distanceFromCamera, dir * 72, dir * 1800, 1, Vector3D(0, -9.81, 0), 5, Vector4(0, 1, 0, 1));
		projectile->setLifeTime(5000);
		break;
	}
	}
}
