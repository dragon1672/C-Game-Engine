#pragma once

#include "ParticleForceGenerator.h"
#include <vector>

class GravityBodyForceGenerator : public ParticleForceGenerator {
public:
	std::vector<Particle *> registeredBodies;
	float gravityConstent;

	void addBody(Particle& toAdd) {
		addBody(&toAdd);
	}
	void addBody(Particle * toAdd) {
		registeredBodies.push_back(toAdd);
	}

	void init(float gravityConstent=1) {
		this->gravityConstent = gravityConstent;
	}

	//override
	void updateForce(Particle * toUpdate) {
		for (int i = 0; i < registeredBodies.size(); i++)
		{
			if(registeredBodies[i] != toUpdate) {
				glm::vec3 diff = registeredBodies[i]->pos - toUpdate->pos;
				float length = glm::length(diff);
				glm::vec3 direction = diff / length;
				float force = (gravityConstent * registeredBodies[i]->mass * toUpdate->mass) / (length * length);
				glm::vec3 totalForce = direction * force;
				toUpdate->addForce(totalForce);
			}
		}
	}
};