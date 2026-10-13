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
	void setColor(Vector4 c) { renderItem->color = c; }
	Vector3D getPos() { return pose.p; }
	void setPos(Vector3D p) { pose.p = p; }

	Vector3D ac;
	float damping;

protected:
	Vector3D vel;
	float mass;
	Vector3D gravity;

private:
	Vector3D antPos;
	physx::PxTransform pose;
	physx::PxShape* shape;
	RenderItem* renderItem;
	bool firstIntegration = true;
};

