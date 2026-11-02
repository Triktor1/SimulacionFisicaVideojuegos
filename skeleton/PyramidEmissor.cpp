#include "PyramidEmissor.h"

PyramidEmissor::PyramidEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
	float baseLX, float endLX, float baseLY, float endLY, float pyramidHeight, float minVel, float maxVel, float minScale, float maxScale,
	float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color),
	baseLX(baseLX), baseLY(baseLY), endLX(endLX), endLY(endLY), pyramidHeight(pyramidHeight) {
}

Particle* PyramidEmissor::getNewParticle(ParticleType type) {
	if (partSystem && active) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			//Dos vectores perpendiculares a la dirección que forman los ejes del plano en el que están las bases de la pirámide
			Vector3D ref = abs(dir.y) < 0.99f ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);
			Vector3D right = dir.cross(ref).normalize();
			Vector3D up = dir.cross(right).normalize();

			//Posiciones aleatorias en los dos cuadrados
			float rndW = newFloat(-baseLX / 2, baseLX / 2);
			float rndH = newFloat(-baseLY / 2, baseLY / 2);
			Vector3D pos1 = pos + right * rndW + up * rndH;
			rndW = rndW / baseLX * endLX;
			rndH = rndH / baseLY * endLY;
			Vector3D pos2 = pos + dir * pyramidHeight + right * rndW + up * rndH;

			//Dirección randomizada de la velocidad de forma que la partícula está dentro del cono
			Vector3D velDir = (pos2 - pos1).normalize();

			p->setVisible(true);
			p->setPos(pos1);
			float l = lifeTime + newFloat(-lifeTimeInterval / 2, lifeTimeInterval / 2);
			p->setLifeTime(l);
			p->setOriginalLifeTime(l);
			p->setVel((velDir * newFloat(minVel, maxVel)));
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