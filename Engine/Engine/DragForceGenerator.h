#pragma once

#include "ParticleForceGenerator.h"
#include <glm\glm.hpp>

class DragForceGenerator : public ParticleForceGenerator {
public:
	float low, high;
	// updated every "updateForce" call
	glm::vec3 lowForce;
	glm::vec3 highForce;
	void init(float low=0, float high=0) {
		this->low = low;
		this->high = high;
	}
	void updateForce(Particle * ctxt) {
		float velLength = glm::length(ctxt->vel);ctxt->vel;
		glm::vec3 normVel = ctxt->vel / velLength;
		lowForce  = -normVel * low * velLength;
		highForce = -normVel * high * velLength * velLength;
		glm::vec3 drag = (lowForce) + (highForce);
		ctxt->totalForce += drag;
	}
};