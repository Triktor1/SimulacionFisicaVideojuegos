#pragma once
#include "ForceGenerator.h"
#include "Particle.h"

class WindForceGenerator :
    public ForceGenerator
{
public:
    WindForceGenerator(Vector3D pos, Vector3D vel, float LX = 20.0f, float LY = 20.0f, float LZ = 20.0f, float k1 = 5, float k2 = 0);
    virtual void updateForce(Particle* particle, double dt) override;
    bool getAABB(Vector3D other) const;
protected:
    Vector3D pos, vel;
    float LX, LY, LZ;
    float k1, k2;
};
