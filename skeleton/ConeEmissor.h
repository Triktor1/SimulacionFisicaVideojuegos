#pragma once
#include "Emisor.h"
class ConeEmissor
	: public Emissor
{
public:
	ConeEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
		float baseR = 5.0f, float endR = 10.0f, float coneHeight = 10.0f,
		float minVel = 1.0f, float maxVel = 2.0f, float minScale = 1.0f, float maxScale = 2.0f,
		float freq = 0.05f, float lifeTime = 5.0f, Vector4 color = Vector4(1, 1, 1, 1));

	Particle* getNewParticle(ParticleType) override;

private:
	float baseR, endR, coneHeight;
};
