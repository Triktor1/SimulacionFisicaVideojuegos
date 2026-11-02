#pragma once
#include "Particle.h"

class StaticParticle :
	public Particle
{
public:
	StaticParticle(Vector3D pos, Vector3D vel, Vector3D ac = Vector3D(), float r = 1.0f, Vector4 color = Vector4(1, 1, 0, 1), float d = 1.0f);

	void setEnlarge(bool e) { enlarge = e; }
	bool getEnlarge() const { return enlarge; }

	void setEnlargeThreshold(float e) { enlargeThreshold = e; }
	float getEnlargeThreshold() const { return enlargeThreshold; }

private:
	bool enlarge = true;

	//El porcentaje de vida restante para que la partícula pase de aumentar a disminuir
	//Si el booleano es true, la partícula empezará con un X% de su tamaño, se agrandará hasta el 100% durante
	//(100-X)% de su tiempo de vida, y luego pasará de 100% a 0% durante el restante X% de tiempo de vida
	float enlargeThreshold = 0.7;
};

