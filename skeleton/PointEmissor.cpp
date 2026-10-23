#include "PointEmissor.h"

PointEmissor::PointEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir, float minVel, float maxVel,
	float minScale, float maxScale, float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color) {
}

Particle* PointEmissor::getNewParticle(ParticleType type) {
	if (partSystem) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			p->setVisible(true);
			p->setPos(pos);
			float l = lifeTime + newFloat(-lifeTimeInterval / 2, lifeTimeInterval / 2);
			p->setLifeTime(l);
			p->setOriginalLifeTime(l);
			p->setVel((dir.normalize() * newFloat(minVel, maxVel)));
			p->setColor(color);
			p->setScale(p->getOriginalScale());
			return p;
		}
	}
}