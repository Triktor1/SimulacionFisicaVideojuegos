#include "PointEmissor.h"

PointEmissor::PointEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir, float minVel, float maxVel,
	float minScale, float maxScale, float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color) {
}

Particle* PointEmissor::getNewParticle(ParticleType type) {
	if (partSystem && active) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			p->setVisible(true);
			p->setActualEmissor(this);
			p->setPos(pos);
			float l = lifeTime + newFloat(-lifeTimeInterval / 2, lifeTimeInterval / 2);
			p->setLifeTime(l);
			p->setOriginalLifeTime(l);
			p->setVel((dir.normalize() * newFloat(minVel, maxVel)));
			//if (type == PROJECTILE) static_cast<Projectile*>(p)->setVelReal(p->getVel() / 5);
			p->setColor(color);
			p->setScale(p->getOriginalScale());
			if (type == STATIC && static_cast<StaticParticle*>(p)->getEnlarge()) {
				StaticParticle* sp = static_cast<StaticParticle*>(p);
				p->setScale(p->getScale() * sp->getEnlargeThreshold());
			}
			return p;
		}
	}
	return nullptr;
}