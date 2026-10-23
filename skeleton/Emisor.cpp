#include "Emisor.h"

Emissor::Emissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir, float minVel, float maxVel,
	float minScale, float maxScale, float freq, float lifeTime, Vector4 color)
	: m_engine(std::random_device{}()), partSystem(ps), type(type), pos(pos), dir(dir), minVel(minVel), maxVel(maxVel),
	minScale(minScale), maxScale(maxScale), freq(freq), lifeTime(lifeTime), color(color), active(true), 
	gravity(Vector3D(0, -10.0f, 0)), normalMean(1), normalStddev(0), randomColor(false) {
}

void Emissor::update(float dt) {
	if (!active || freq <= 0.0f) return;

	timeToEmit -= dt;

	if (timeToEmit <= 0.0f) {
		if (randomColor) {
			float r, g, b;
			r = newFloat(0, 1);
			g = newFloat(0, 1);
			b = newFloat(0, 1);
			color = Vector4(r, g, b, 1.0f);
		}
		Particle* p = getNewParticle(type);
		p->setOriginalScale(newFloat(minScale, maxScale));
		timeToEmit = freq;
	}
}

void Emissor::setNormalDistribution(float min, float max) {
	normalMean = min + (max - min) / 2;
	if (normalStddev == 0)
		normalDist = std::normal_distribution<float>(normalMean, 1);
	else normalDist = std::normal_distribution<float>(normalMean, normalStddev);
}

void Emissor::setUniformDistribution(float min, float max) {
	if (min > max)
		uniformDist = std::uniform_real_distribution<float>(min);
	else uniformDist = std::uniform_real_distribution<float>(min, max);
}

void Emissor::setDistrubution(Distribution d, float stddev) {
	dist = d;
	if (dist == NORMAL) {
		normalStddev = stddev;
	}

}

float Emissor::newFloat(float min, float max) {
	float rnd;
	switch (dist) {
	case UNIFORM:
		setUniformDistribution(min, max);
		rnd = uniformDist(m_engine);
		break;
	case NORMAL:
		setNormalDistribution(min, max);
		do {
			rnd = normalDist(m_engine);
		} while (rnd<min || rnd>max);
		break;
	}
	return rnd;
}