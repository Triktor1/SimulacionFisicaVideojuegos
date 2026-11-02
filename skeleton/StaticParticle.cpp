#include "StaticParticle.h"

StaticParticle::StaticParticle(Vector3D pos, Vector3D vel, Vector3D ac, float r, Vector4 color, float d)
	: Particle(pos, vel, ac, r, color, d, Vector3D(0,0,0)) {

}
