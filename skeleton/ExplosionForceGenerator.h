#pragma once
#include "ForceGenerator.h"

class ExplosionForceGenerator :
    public ForceGenerator
{
public:
    ExplosionForceGenerator(Vector3D pos, float T, float K, float expansionVel = 343.2f);
    void updateForce(Particle* particle, double dt) override;
    void updateTime(double dt) override;
    void setActive(bool a) override;
private:
    Vector3D pos;
    float R, T, K, tAct, expansionVel;
};

