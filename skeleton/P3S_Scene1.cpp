#include "P3S_Scene1.h"

void P3S_Scene1::init() {
	ps = new ParticleSystem();

	emissors.push_back(new ConeEmissor(ps, ParticleType::PARTICLE, Vector3D(0, 0, 0), Vector3D(0, 1, 0), 3, 30, 100, 30, 50, 1, 2.5, 0.005, 5000));
	emissors.back()->setColor(Vector4(0, 0, 0.7, 1));

	ps->addGeneratorToAll(new WhirlwindForceGenerator(Vector3D(0, 40, 0), 10, 400, 60, 400));
}

void P3S_Scene1::update(double dt) {
	ps->update(dt);
	for (Emissor* e : emissors) {
		e->update(dt);
	}
}

void P3S_Scene1::cleanup() {
	for (auto& e : emissors) {
		delete e;
	}
	delete ps;
}