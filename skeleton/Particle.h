#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3D pos, Vector3D vel, Vector3D ac = Vector3D(), float r = 1.0f, Vector4 color = Vector4(1, 1, 0, 1), float d = 1.0f);
	~Particle();

	void euler(double t);
	void semiImplicitEuler(double t);
	void verlet(double t);

	void setShape(physx::PxShape* s);
	void setColor(Vector4 c) {renderItem->color = c;}

	Vector3D ac;
	float damping;
private:
	Vector3D antPos;
	Vector3D vel;
	float mass;
	Vector3D gravity;//?
	physx::PxTransform pose;
	physx::PxShape* shape;
	RenderItem* renderItem;
	bool firstIntegration = true;
};

