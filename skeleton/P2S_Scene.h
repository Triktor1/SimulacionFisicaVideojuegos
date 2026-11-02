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

class P2S_Scene :
    public EmptyScene
{
public:
    explicit P2S_Scene(std::string name) : EmptyScene(std::move(name)) {};

    void init() override;
    void cleanup() override;
    void update(double dt) override;
private:
    std::vector<Emissor*> emissors;
    ParticleSystem* ps;
    Vector4 c = Vector4(0, 0, 0, 1);
};
