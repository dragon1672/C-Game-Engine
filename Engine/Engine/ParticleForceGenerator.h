#pragma once

#include "Particle.h"

class ParticleForceGenerator {
public:
	virtual void updateForce(Particle * ctxt) = 0;
};