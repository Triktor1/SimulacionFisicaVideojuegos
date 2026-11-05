#include "CircleEmissor.h"

CircleEmissor::CircleEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
	float r, float minVel, float maxVel, float minScale, float maxScale,
	float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color), r(r) {
}

Particle* CircleEmissor::getNewParticle(ParticleType type) {
	if (partSystem && active) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			//Dos vectores perpendiculares a la dirección que forman los ejes del plano en el que están las bases del cono
			Vector3D ref = abs(dir.y) < 0.99f ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);
			Vector3D right = dir.cross(ref).normalize();
			Vector3D up = dir.cross(right).normalize();

			//Posiciones aleatorias en los dos círculos
			float rndAngle = newFloat(0, 2 * std::_Pi_val);
			float R = std::sqrt(newFloat(0.0f, 1.0f));
			Vector3D position = pos + right * (R * r * std::cos(rndAngle)) + up * (R * r * std::sin(rndAngle));

			p->setVisible(true);
			p->setActualEmissor(this);
			p->setPos(position);
			float l = lifeTime + newFloat(-lifeTimeInterval / 2, lifeTimeInterval / 2);
			p->setLifeTime(l);
			p->setOriginalLifeTime(l);
			p->setVel((dir * newFloat(minVel, maxVel)));
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