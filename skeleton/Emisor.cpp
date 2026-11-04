#include "Emisor.h"

Emissor::Emissor(ParticleSystem* ps, ParticleType type, Vector3D pos, Vector3D dir, float minVel, float maxVel,
	float minScale, float maxScale, float freq, float lifeTime, Vector4 color)
	: m_engine(std::random_device{}()), partSystem(ps), type(type), pos(pos), dir(dir.normalize()), minVel(minVel), maxVel(maxVel),
	minScale(minScale), maxScale(maxScale), freq(freq), lifeTime(lifeTime), color(color), active(true),
	gravity(Vector3D(0, -10.0f, 0)), normalMean(1), normalStddev(0), randomColor(false) {
	if (ps) {
		ps->registerEmissor(this);
	}
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
		if (p) {
			p->clearForceGenerators();
			p->setOriginalScale(newFloat(minScale, maxScale));
			if (type == STATIC && static_cast<StaticParticle*>(p)->getEnlarge()) {
				StaticParticle* sp = static_cast<StaticParticle*>(p);
				sp->setScale(sp->getOriginalScale() * sp->getEnlargeThreshold());
			}
			else p->setScale(p->getOriginalScale());

			for (auto f : generators) {
				p->addForceGenerator(f);
			}
		}
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

void Emissor::setGeneratorsActive(bool a) {
	for (auto f : generators) {
		f->setActive(a);
	}
}

void Emissor::addGenerator(ForceGenerator* f) {
	generators.push_back(f);
}