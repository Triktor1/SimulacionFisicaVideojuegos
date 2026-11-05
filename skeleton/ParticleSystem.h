#pragma once
#include "StaticParticle.h"
#include <unordered_map>
#include <random>

static constexpr int PARTICLE_NUM = 2500;

enum ParticleType {
	PARTICLE = 0,
	STATIC,
	NUM_TYPES
};

class Emissor;
class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void update(float dt);
	Particle* getParticle(ParticleType);

	void setReduceScale(bool s) { reduceScale = s; }
	void registerEmissor(Emissor*);
	void addGeneratorToAll(ForceGenerator*);
	void setActiveToAll(bool a);

private:
	std::unordered_map<ParticleType, std::vector<Particle*>> particles;
	std::vector<Emissor*> emissors;
	bool reduceScale;
};