#pragma once
#include "Emisor.h"
class PyramidEmissor :
    public Emissor
{
public:
	PyramidEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
		float baseLX = 5.0f, float endLX = 10.0f, float baseLY = 5.0f, float endLY = 10.0f, float coneHeight = 10.0f,
		float minVel = 1.0f, float maxVel = 2.0f, float minScale = 1.0f, float maxScale = 2.0f,
		float freq = 0.05f, float lifeTime = 5.0f, Vector4 color = Vector4(1, 1, 1, 1));

	Particle* getNewParticle(ParticleType) override;

private:
	float baseLX, baseLY, endLX, endLY, pyramidHeight;
};

