#include "P3S_Scene1.h"

void P3S_Scene1::init() {
	ps = new ParticleSystem();

	coneEm1 = new ConeEmissor(ps, ParticleType::PARTICLE, Vector3D(-40, 0, 0), Vector3D(1, 1, 0), 3, 30, 100, 30, 50, 1, 2.5, 0.005, 5000);
	emissors.push_back(coneEm1);
	emissors.back()->setInterpolatedColors(true, Vector4(0, 0, 1, 1), Vector4(0, 1, 1, 1));
	emissors.back()->setDistribution(NORMAL);

	coneEm2 = new ConeEmissor(ps, ParticleType::PARTICLE, Vector3D(0, 0, 0), Vector3D(0, 1, 0), 3, 30, 100, 30, 50, 1, 2.5, 0.005, 5000);
	emissors.push_back(coneEm2);

	sphereEm = new SphereEmissor(ps, ParticleType::PARTICLE, Vector3D(30, 0, -50), Vector3D(0, 1, 0), 10, 0, 0, 1, 1.5, 0.005, 5000);
	emissors.push_back(sphereEm);
	emissors.back()->setRandomColors(true);

	wfg = new WhirlwindForceGenerator(Vector3D(0, 40, 0), 10, 400, 60, 400);
	generators.push_back(wfg);
	ps->addGeneratorToAll(wfg);

	efg = new ExplosionForceGenerator(Vector3D(30, 0, -50), 500, 40000);
	generators.push_back(efg);
	ps->addGeneratorToAll(efg);
	efg->setActive(false);

	gfg = new GravityForceGenerator(Vector3D(0, -9.81, 0));
	generators.push_back(gfg);
	ps->addGeneratorToAll(gfg);
}

void P3S_Scene1::update(double dt) {
	ps->update(dt);
	for (Emissor* e : emissors) {
		e->update(dt);
	}
	for (ForceGenerator* f : generators) {
		f->updateTime(dt);
	}
}

void P3S_Scene1::cleanup() {
	for (auto& e : emissors) {
		delete e;
	}
	for (ForceGenerator* f : generators) {
		delete f;
	}

	delete ps;
}

void P3S_Scene1::keyPress(unsigned char key, const physx::PxTransform& camera) {
	switch (key) {
	case 'p': case 'P':
		efg->setActive(!efg->getActive());
		break;
	case 'o': case 'O':
		wfg->setActive(!wfg->getActive());
		break;
	case 'i': case 'I':
		gfg->setActive(!gfg->getActive());
		break;
	case 'j': case 'J':
		coneEm1->setActive(!coneEm1->getActive());
		break;
	case 'k': case 'K':
		coneEm2->setActive(!coneEm2->getActive());
		break;
	case 'l': case 'L':
		sphereEm->setActive(!sphereEm->getActive());
		break;
	}
}
