#include "RectEmissor.h"

RectEmissor::RectEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
	float LX, float LY, float minVel, float maxVel, float minScale, float maxScale,
	float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color), LX(LX), LY(LY) {
}

Particle* RectEmissor::getNewParticle(ParticleType type) {
	if (partSystem && active) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			//Dos vectores perpendiculares a la dirección que forman los ejes del plano en el que están las bases de la pirámide
			Vector3D ref = abs(dir.y) < 0.99f ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);
			Vector3D right = dir.cross(ref).normalize();
			Vector3D up = dir.cross(right).normalize();

			//Posiciones aleatorias en los dos cuadrados
			float rndW = newFloat(-LX / 2, LX / 2);
			float rndH = newFloat(-LY / 2, LY / 2);
			Vector3D position = pos + right * rndW + up * rndH;

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