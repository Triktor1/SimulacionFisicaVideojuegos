#include "RectEmissor.h"

RectEmissor::RectEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
	float l, float minVel, float maxVel, float minScale, float maxScale,
	float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color), l(l) {
}

Particle* RectEmissor::getNewParticle(ParticleType type) {
	if (partSystem) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			//Dos vectores perpendiculares a la dirección que forman los ejes del plano en el que están las bases de la pirámide
			Vector3D ref = abs(dir.y) < 0.99f ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);
			Vector3D right = dir.cross(ref).normalize();
			Vector3D up = dir.cross(right).normalize();

			//Posiciones aleatorias en los dos cuadrados
			float rndW = newFloat(-l / 2, l / 2);
			float rndH = newFloat(-l / 2, l / 2);
			Vector3D position = pos + right * rndW + up * rndH;

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