#pragma once
#include "ParticleSystem.h"
#include <random>
#include <numeric>

enum Distribution {
	UNIFORM,
	NORMAL,
	POISSON
};

class Emissor
{
public:
	Emissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir,
		float minVel = 1.0f, float maxVel = 2.0f,
		float freq = 1.0f, float lifeTime = 5.0f,
		Vector4 color = Vector4(1, 1, 1, 1));

	void update(float dt);


	//Cambia la distribución aleatoria del emisor. 
	//Las variables adicionales se usan solo en caso de que se elija una distribución:
	//NORMAL (normalStddev)
	void setDistrubution(Distribution, float stddev = 1.0f);

	void setFreq(float f) { freq = f; }
	void setColor(Vector4 c) { color = c; }
	void setLifeTime(float l) { lifeTime = l; }
	void setRandomColors(bool r) { randomColor = r; }

	virtual void getNewParticle(ParticleType) = 0;

protected:
	ParticleSystem* partSystem;
	std::mt19937 m_engine;
	float freq;
	float lifeTime;
	float minVel, maxVel;
	float normalMean, normalStddev;

	Vector3D pos, dir, gravity;
	Vector4 color;

	bool active, randomColor;

	ParticleType type = ParticleType::PARTICLE;
	Distribution dist = NORMAL;

	std::normal_distribution<float> normalDist;
	std::uniform_real_distribution<float> uniformDist;

	const float lifeTimeInterval = 10.0f;

	float newFloat(float, float);

private:
	void setNormalDistribution(float, float);
	void setUniformDistribution(float, float);
};