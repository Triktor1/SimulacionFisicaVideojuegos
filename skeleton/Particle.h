#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "SceneManager.h"

class ForceGenerator;
class Emissor;
class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, float r = 1.0f, Vector4 color = Vector4(1, 1, 0, 1), float d = 1.0f, float mass = 5.0f);
	~Particle();

	virtual void euler(double t);
	virtual void semiImplicitEuler(double t);
	virtual void verlet(double t);

	void setShape(physx::PxShape* s);
	void setColor(Vector4 c);
	void setPos(Vector3D p) { pose.p = p; antPos = p; }
	void setVel(Vector3D v) { vel = v; }
	void addForce(Vector3D f) { forceAcc += f; }
	void setMass(float m) { mass = m; }
	void setVisible(bool v);
	void setLifeTime(float l) { lifeTime = l; }
	void setOriginalLifeTime(float l) { originalLifeTime = l; }
	void setScale(float s) { renderItem->scale = s; scale = s; }
	void setOriginalScale(float s) { iniScale = s; }
	void setActualEmissor(Emissor* e) { actEmissor = e; }

	Vector4 getColor() const { return color; }
	Vector3D getPos() const { return pose.p; }
	Vector3D getVel() const { return vel; }
	Vector3D getForceAccumulator() { return forceAcc; }
	float getMass() const { return mass; }
	bool getAlive() const { return isAlive; };
	float getLifeTime() const { return lifeTime; }
	float getOriginalLifeTime() const { return originalLifeTime; }
	float getScale() const { return scale; }
	float getOriginalScale() const { return iniScale; }
	Emissor* getActualEmissor() { if (actEmissor) return actEmissor; return nullptr; }

	virtual void updateForces(double dt);
	void clearForces();

	void clearForceGenerators() { forceGenerators.clear(); };
	void addForceGenerator(ForceGenerator* f) { forceGenerators.push_back(f); }

	float damping;

protected:
	Vector3D vel;
	Vector3D forceAcc;
	float mass;
	float w;
	float lifeTime = 0;
	float originalLifeTime = 0;
	float scale = 1;
	float iniScale = 1;
private:
	Vector3D antPos;
	Vector4 color;
	physx::PxTransform pose;
	RenderItem* renderItem;
	bool firstIntegration = true;
	bool isAlive = true;
	Emissor* actEmissor = nullptr;
	std::vector<ForceGenerator*> forceGenerators;
};

