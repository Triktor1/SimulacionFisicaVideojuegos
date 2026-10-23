#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D ac = Vector3D(), float r = 1.0f, Vector4 color = Vector4(1, 1, 0, 1), float d = 1.0f, Vector3D gravity = Vector3D(0, -9.81, 0), float mass = 5.0f);
	~Particle();

	virtual void euler(double t);
	virtual void semiImplicitEuler(double t);
	virtual void verlet(double t);

	void setShape(physx::PxShape* s);
	void setColor(Vector4 c) { renderItem->color = c; color = c; }
	void setPos(Vector3D p) { pose.p = p; antPos = p; }
	void setVel(Vector3D v) { vel = v; }
	void setMass(float m) { mass = m; }
	void setVisible(bool v);
	void setLifeTime(float l) { lifeTime = l; }
	void setOriginalLifeTime(float l) { originalLifeTime = l; }
	void setScale(float s) { setShape(CreateShape(physx::PxSphereGeometry(s))); scale = s; }
	void setOriginalScale(float s) { iniScale = s; }

	Vector4 getColor() const { return color; }
	Vector3D getPos() const { return pose.p; }
	Vector3D getVel() const { return vel; }
	float getMass() const { return mass; }
	bool getVisible() const { return renderItem != nullptr; };
	float getLifeTime() const { return lifeTime; }
	float getOriginalLifeTime() const { return originalLifeTime; }
	float getScale() const { return scale; }
	float getOriginalScale() const { return iniScale; }

	Vector3D ac;
	float damping;

protected:
	Vector3D vel;
	float mass;
	Vector3D gravity;
	float lifeTime = 0;
	float originalLifeTime = 0;
	float scale = 1;
	float iniScale = 1;
private:
	Vector3D antPos;
	physx::PxTransform pose;
	RenderItem* renderItem;
	bool firstIntegration = true;
	Vector4 color;
};

