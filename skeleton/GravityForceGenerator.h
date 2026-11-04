#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator :
    public ForceGenerator
{
public:
    GravityForceGenerator(Vector3D gravity);
    void updateForce(Particle* particle, double dt) override;
    void setGravity(Vector3D g);

private:
    Vector3D gravity;
};

