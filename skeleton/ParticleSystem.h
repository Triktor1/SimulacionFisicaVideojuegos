#pragma once
#include "Projectile.h"
#include <unordered_map>
#include <random>

static constexpr int PARTICLE_NUM = 2000;

enum ParticleType {
	PROJECTILE = 0,
	PARTICLE,
	NUM_TYPES
};

class ParticleSystem
{
public:
	ParticleSystem();

	void update(float dt);
	Particle* getParticle(ParticleType);

private:
	std::unordered_map<ParticleType, std::vector<Particle*>> particles;

};