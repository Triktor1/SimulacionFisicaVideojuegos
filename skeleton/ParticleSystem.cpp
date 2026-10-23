#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
	ParticleType type = (ParticleType)0;
	for (int i = 0; i < PARTICLE_NUM; i++) {
		switch (type) {
		case PROJECTILE:
			particles[PROJECTILE].push_back(new Projectile(Vector3D(), Vector3D(), Vector3D()));
			particles[PROJECTILE].back()->setVisible(false);
			break;
		case PARTICLE:
			particles[PARTICLE].push_back(new Particle(Vector3D(), Vector3D()));
			particles[PARTICLE].back()->setVisible(false);
			break;
		}
		type = (ParticleType)((type + 1) % NUM_TYPES);
	}
}

void ParticleSystem::update(float dt) {
	for (auto part : particles) {
		for (Particle* p : part.second) {
			if (p && p->getVisible()) {
				//Integrar
				p->verlet(dt);

				//Reducimos el tamaño en función de su tamaño original y la vida que ha perdido
				p->setScale(p->getScale() * (p->getLifeTime() / p->getOriginalLifeTime()));

				//Le quitamos tiempo de vida
				p->setLifeTime(p->getLifeTime() - dt*1000);
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
