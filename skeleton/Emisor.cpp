#include "Emisor.h"

Emissor::Emissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir, float minVel, float maxVel,
	float minScale, float maxScale, float freq, float lifeTime, Vector4 color)
	: m_engine(std::random_device{}()), partSystem(ps), type(type), pos(pos), dir(dir.normalize()), minVel(minVel), maxVel(maxVel),
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
		if (p)
			p->setOriginalScale(newFloat(minScale, maxScale));
		timeToEmit = freq;
	}
}

void Emissor::applyDistribution(float min, float max) {
	if (min > max) std::swap(min, max);
	switch (dist) {
	case UNIFORM:
		uniformDist = std::uniform_real_distribution<float>(min, max);
		break;
	case NORMAL:
		normalMean = (min + max) / 2;
		normalStddev = (max - min) / 6;
		if (normalStddev == 0) normalStddev = 0.01;
		normalDist = std::normal_distribution<float>(normalMean, normalStddev);
		break;
	}
}

void Emissor::setDistribution(Distribution d) {
	dist = d;
}

float Emissor::newFloat(float min, float max) {
	float rnd;
	switch (dist) {
	case UNIFORM:
		applyDistribution(min, max);
		rnd = uniformDist(m_engine);
		break;
	case NORMAL:
		applyDistribution(min, max);
		rnd = normalDist(m_engine);
		break;
	}
	return rnd;
}