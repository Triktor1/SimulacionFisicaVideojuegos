#pragma once
#include "ParticleSystem.h"
#include <random>
#include <numeric>

enum Distribution {
	UNIFORM,
	NORMAL
};

class Emissor
{
public:
	Emissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
		float minVel = 1.0f, float maxVel = 2.0f, float minScale = 1.0f, float maxScale = 3.0f,
		float freq = 1.0f, float lifeTime = 5.0f,
		Vector4 color = Vector4(1, 1, 1, 1));

	void update(float dt);

	//Cambia la distribución aleatoria del emisor. 
	void setDistribution(Distribution);

	void setFreq(float f) { freq = f; }
	void setColor(Vector4 c) { color = c; }
	void setLifeTime(float l) { lifeTime = l; }
	void setRandomColors(bool r) { randomColor = r; interpolatedColor = false; }
	void setInterpolatedColors(bool i, Vector4 c1 = Vector4(1, 1, 1, 1), Vector4 c2 = Vector4(0, 0, 0, 1));
	void setMinScale(float s) { minScale = s; }
	void setMaxScale(float s) { maxScale = s; }
	void setMinVel(float s) { minVel = s; }
	void setMaxVel(float s) { maxVel = s; }
	void setLifeTimeInterval(float t) { lifeTimeInterval = t; }
	void setActive(bool a) { active = a; }
	void setGeneratorsActive(bool a);

	virtual Particle* getNewParticle(ParticleType) = 0;
	bool getActive() const { return active; };
	bool getInterpolatingColors() { return interpolatedColor; };
	Vector4 getActualInterpolatedColor(float proportion);

	void addGenerator(ForceGenerator*);

protected:
	ParticleSystem* partSystem;
	std::mt19937 m_engine;
	float freq;
	float lifeTime;
	float minVel, maxVel;
	float normalMean, normalStddev;
	float minScale, maxScale;

	Vector3D pos, dir, gravity;
	Vector4 color;
	Vector4 interpolatedColor1, interpolatedColor2;

	bool active, randomColor, interpolatedColor;

	ParticleType type = ParticleType::PARTICLE;
	Distribution dist = UNIFORM;

	std::normal_distribution<float> normalDist;
	std::uniform_real_distribution<float> uniformDist;

	float lifeTimeInterval = 500.0f;

	float newFloat(float, float);

private:
	float timeToEmit = 0.0f;

	void applyDistribution(float, float);
	std::vector<ForceGenerator*> generators;
};