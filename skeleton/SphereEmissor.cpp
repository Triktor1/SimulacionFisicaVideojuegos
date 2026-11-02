#include "SphereEmissor.h"

SphereEmissor::SphereEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
	float r, float minVel, float maxVel, float minScale, float maxScale,
	float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color), r(r) {
}

Particle* SphereEmissor::getNewParticle(ParticleType type) {
	if (partSystem && active) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			float u = newFloat(0.0f, 1.0f);
			float v = newFloat(0.0f, 1.0f);

			float theta = 2.0f * std::_Pi_val * u;
			float phi = std::acos(1.0f - 2.0f * v);

			Vector3D rndPoint(
				std::sin(phi) * std::cos(theta),
				std::sin(phi) * std::sin(theta),
				std::cos(phi)
			);

			float R = std::cbrt(newFloat(0.0f, 1.0f));
			Vector3D position = pos + rndPoint * R * r;

			p->setVisible(true);
			p->setPos(position);
			float l = lifeTime + newFloat(-lifeTimeInterval / 2, lifeTimeInterval / 2);
			p->setLifeTime(l);
			p->setOriginalLifeTime(l);
			p->setVel((dir * newFloat(minVel, maxVel)));
			p->setColor(color);
			p->setScale(p->getOriginalScale());
			return p;
		}
	}
	return nullptr;
}