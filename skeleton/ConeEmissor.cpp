#include "ConeEmissor.h"

ConeEmissor::ConeEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
	float baseR, float endR, float coneHeight, float minVel, float maxVel, float minScale, float maxScale,
	float freq, float lifeTime, Vector4 color)
	: Emissor(ps, type, pos, dir, minVel, maxVel, minScale, maxScale, freq, lifeTime, color),
	baseR(baseR), endR(endR), coneHeight(coneHeight) {
}

Particle* ConeEmissor::getNewParticle(ParticleType type) {
	if (partSystem && active) {
		Particle* p = partSystem->getParticle(type);
		if (p) {
			//Dos vectores perpendiculares a la dirección que forman los ejes del plano en el que están las bases del cono
			Vector3D ref = abs(dir.y) < 0.99f ? Vector3D(0, 1, 0) : Vector3D(1, 0, 0);
			Vector3D right = dir.cross(ref).normalize();
			Vector3D up = dir.cross(right).normalize();

			//Posiciones aleatorias en los dos círculos
			float rndAngle = newFloat(0, 2 * std::_Pi_val);
			float r = std::sqrt(newFloat(0.0f, 1.0f));
			Vector3D pos1 = pos + right * (r * baseR * std::cos(rndAngle)) + up * (r * baseR * std::sin(rndAngle));
			Vector3D pos2 = pos + dir * coneHeight + right * (r * endR * std::cos(rndAngle)) + up * (r * endR * std::sin(rndAngle));

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
			return p;
		}
	}
	return nullptr;
}