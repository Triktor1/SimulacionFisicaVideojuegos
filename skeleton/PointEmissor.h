#pragma once
#include "Emisor.h"
class PointEmissor :
    public Emissor
{
public:
    PointEmissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
		float minVel = 1.0f, float maxVel = 2.0f,
		float freq = 0.05f, float lifeTime = 5.0f,
		Vector4 color = Vector4(1, 1, 1, 1));

    void getNewParticle(ParticleType) override;
};  

