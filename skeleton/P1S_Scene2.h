#pragma once
#include "EmptyScene.h"
#include "Particle.h"
#include "Projectile.h"

class P1S_Scene2 :
    public EmptyScene
{
public:
    explicit P1S_Scene2(std::string name) : EmptyScene(std::move(name)) {}
    void init() override;
    void cleanup() override;
    void update(double dt) override;
    void keyPress(unsigned char key, const physx::PxTransform& camera) override;
private:
    std::vector<physx::PxTransform*> transforms;
    std::vector<RenderItem*> renderItems;
    std::vector<Particle*> projectiles;
};
