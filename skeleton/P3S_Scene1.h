#pragma once
#include "EmptyScene.h"
#include "Particle.h"
#include "PointEmissor.h"
#include "ConeEmissor.h"
#include "SphereEmissor.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"

class P3S_Scene1 :
	public EmptyScene
{
public:
	explicit P3S_Scene1(std::string name) : EmptyScene(std::move(name)) {};

	void init() override;
	void cleanup() override;
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;
private:
	std::vector<Emissor*> emissors;
	std::vector<ForceGenerator*> generators;
	ParticleSystem* ps;
	GravityForceGenerator* gfg;
	WhirlwindForceGenerator* wfg;
	ExplosionForceGenerator* efg;

	ConeEmissor* coneEm1, *coneEm2;
	SphereEmissor* sphereEm;
};

