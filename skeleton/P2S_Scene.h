#pragma once
#include "EmptyScene.h"
#include "Particle.h"
#include "Projectile.h"
#include "PointEmissor.h"
#include "ConeEmissor.h"
#include "PyramidEmissor.h"
#include "CircleEmissor.h"
#include "RectEmissor.h"
#include "CubeEmissor.h"
#include "SphereEmissor.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "ExplosionForceGenerator.h"

class P2S_Scene :
    public EmptyScene
{
public:
    explicit P2S_Scene(std::string name) : EmptyScene(std::move(name)) {};

    void init() override;
    void cleanup() override;
    void update(double dt) override;
    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
private:
    std::vector<Emissor*> emissors;
    std::vector<ForceGenerator*> generators;
    ParticleSystem* ps;
};
