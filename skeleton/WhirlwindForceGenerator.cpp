#include "WhirlwindForceGenerator.h"

WhirlwindForceGenerator::WhirlwindForceGenerator(Vector3D pos, float k, float LX = 20.0f, float LY = 20.0f, float LZ = 20.0f) :
	WindForceGenerator(pos, Vector3D(), LX, LY, LZ), K(k) {
}

void WhirlwindForceGenerator::updateForce(Particle* particle, double dt) {
	//Calculamos la velocidad del torbellino según la posición de la partícula
	if (particle->getMass() <= 0)
		return;
	if (active && getAABB(particle->getPos())) {
		Vector3D partPos = particle->getPos();
		//Aunque no sigue la fórmula del enunciado, he tenido que cambiar el eje Y para evitar propulsiones
		//desproporcionadamente grandes (salían súper rápido y no se apreciaba la rotación)
		vel = Vector3D(-(partPos.z - pos.z), 2-(partPos.y-pos.y), partPos.x - pos.x) * K;

		//Calculamos la fuerza del viento según esta nueva velocidad
		WindForceGenerator::updateForce(particle, dt);
	}
}