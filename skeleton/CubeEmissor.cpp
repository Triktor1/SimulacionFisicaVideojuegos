#include "CubeEmissor.h"

CubeEmissor::CubeEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
	float LX, float LY, float LZ, float minVel, float maxVel, float minScale, float maxScale,
	float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color), LX(LX), LY(LY), LZ(LZ) {
}

Particle* CubeEmissor::getNewParticle(ParticleType type) {
	if (partSystem && active) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			//Posiciones aleatorias en los dos cuadrados
			float rndW = newFloat(-LX / 2, LX / 2);
			float rndH = newFloat(-LY / 2, LY / 2);
			float rndD = newFloat(-LZ / 2, LZ / 2);
			Vector3D position = pos + Vector3D(rndW, rndH, rndD);

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