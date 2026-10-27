#pragma once
#include "EmptyScene.h"
#include "Particle.h"
#include "Projectile.h"
#include "PointEmissor.h"
#include "ConeEmissor.h"
#include "PyramidEmissor.h"
#include "CircleEmissor.h"
#include "RectEmissor.h"

class P1S_Scene :
    public EmptyScene
{
public:
    explicit P1S_Scene(std::string name) : EmptyScene(std::move(name)) {};
    
    void init() override;
    void cleanup() override;
    void update(double dt) override;
private:
    std::vector<physx::PxTransform*> transforms;
    std::vector<RenderItem*> renderItems;
    std::vector<Particle*> particles;
    std::vector<Emissor*> emissors;
    ParticleSystem* ps;
};
