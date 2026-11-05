#pragma once
#include "EmptyScene.h"
#include "Particle.h"
#include "PointEmissor.h"
#include "ConeEmissor.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"

class P3S_Scene1 :
	public EmptyScene
{
public:
	explicit P3S_Scene1(std::string name) : EmptyScene(std::move(name)) {};

	void init() override;
	void cleanup() override;
	void update(double dt) override;
private:
	std::vector<Emissor*> emissors;
	ParticleSystem* ps;

};

