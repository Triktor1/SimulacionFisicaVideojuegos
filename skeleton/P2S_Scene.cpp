#include "P2S_Scene.h"

void P2S_Scene::init() {
	ps = new ParticleSystem();
	//Burbujas de veneno
	emissors.push_back(new CubeEmissor(ps, ParticleType::STATIC, Vector3D(50, 0, 0), Vector3D(0, 1, 0), 80, 30, 80, 1, 5, 1, 1.5, 0.005, 10000));
	emissors.back()->setColor(Vector4(76/255.0f, 40/255.0f, 130/255.0f, 1));

	//Fuente oscura (Dark Fountain de DELTARUNE)
	emissors.push_back(new ConeEmissor(ps, ParticleType::STATIC, Vector3D(0, 20, 0), Vector3D(0, 1, 0), 3, 30, 100, 30, 40, 1, 2.5, 0.005, 5000));
	emissors.back()->setColor(Vector4(0, 0, 0, 1));

	//Cañón de bolas de colorines
	emissors.push_back(new ConeEmissor(ps, ParticleType::PARTICLE, Vector3D(50, 40, 0), Vector3D(1, 1, 0), 3, 30, 100, 30, 40, 0.75, 1.5, 0.02, 6000));
	emissors.back()->setRandomColors(true);
}

void P2S_Scene::update(double dt) {
	ps->update(dt);
	for (Emissor* e : emissors) {
		e->update(dt);
	}
}

void P2S_Scene::cleanup() {
	for (auto& e : emissors) {
		delete e;
	}
	delete ps;
}