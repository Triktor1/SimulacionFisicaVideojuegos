#pragma once
#include "WindForceGenerator.h"
class WhirlwindForceGenerator :
    public WindForceGenerator
{
public:
    WhirlwindForceGenerator(Vector3D pos, float k, float LX, float LY, float LZ);
    void updateForce(Particle* particle, double dt) override;
private:
    float K;
};

