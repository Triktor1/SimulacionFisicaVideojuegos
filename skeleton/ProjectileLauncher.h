#pragma once
#include <vector>
#include "Vector3D.h"
#include "RenderUtils.hpp"

class GravityForceGenerator;
class Projectile;
class ProjectileLauncher
{
public:
	ProjectileLauncher();
	Projectile* shoot(Vector3D pos, Vector3D velSim, Vector3D velReal, float r = 1.0f, Vector3D gravityReal = Vector3D(0, -9.81, 0), float mass = 5.0f, Vector4 color = Vector4(1, 1, 0, 1), float d = 1.0f);
	void update(float dt);
	void setGravity(Vector3D);
	~ProjectileLauncher();

private:
	GravityForceGenerator* gravityForce;
	std::vector<Projectile*> projectiles;
};

