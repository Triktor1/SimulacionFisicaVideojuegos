#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : reduceScale(true) {
	ParticleType type = (ParticleType)0;
	for (int i = 0; i < PARTICLE_NUM; i++) {
		switch (type) {
		case PARTICLE:
			particles[PARTICLE].push_back(new Particle(Vector3D(), Vector3D()));
			particles[PARTICLE].back()->setVisible(false);
			break;
		case STATIC:
			particles[STATIC].push_back(new StaticParticle(Vector3D(), Vector3D()));
			particles[STATIC].back()->setVisible(false);
			break;
		}
		type = (ParticleType)((type + 1) % NUM_TYPES);
	}
}

void ParticleSystem::update(float dt) {
	for (auto part : particles) {
		for (Particle* p : part.second) {
			if (p && p->getAlive()) {
				//Integrar
				p->verlet(dt);

				//Reducimos el tamaño en función de su tamaño original y la vida que ha perdido
				if (reduceScale) {
					//Hago static cast aunque es un vector de Particle porque sé al 100% 
					//que la partícula es de tipo StaticParticle por la comprobación previa
					float lifeProportion = p->getLifeTime() / p->getOriginalLifeTime();
					float sc = 0;
					if (part.first == STATIC && static_cast<StaticParticle*>(p)->getEnlarge()) {
						StaticParticle* sp = static_cast<StaticParticle*>(p);
						if (lifeProportion >= sp->getEnlargeThreshold()) {
							sc = p->getOriginalScale() * (sp->getEnlargeThreshold() + (1 - lifeProportion));
						}
						else {
							sc = p->getOriginalScale() * (lifeProportion / sp->getEnlargeThreshold());
						}
					}
					else {
						sc = p->getOriginalScale() * lifeProportion;
					}
					if (sc == 0) sc = 0.0001f;
					p->setScale(sc);
				}

				//Le quitamos tiempo de vida
				p->setLifeTime(p->getLifeTime() - dt * 1000);
				if (p->getLifeTime() <= 0)
					p->setVisible(false);
			}
		}
	}
}

Particle* ParticleSystem::getParticle(ParticleType type) {
	std::vector<Particle*> v = particles[type];
	for (Particle* p : v) {
		if (p && p->getLifeTime() <= 0)
			return p;
	}
	return nullptr;
}

ParticleSystem::~ParticleSystem() {
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		for (Particle* p : (*it).second) {
			delete p;
		}
	}
}