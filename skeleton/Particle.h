#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D ac = Vector3D(), float d = 1);
	~Particle();

	void integrate(double t);

	Vector3D ac;
	float damping;
private:
	Vector3D vel;
	physx::PxTransform pose;
	physx::PxShape* shape;
	RenderItem* renderItem;

};

