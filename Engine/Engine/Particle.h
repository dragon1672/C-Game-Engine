#pragma once

#include <glm/glm.hpp>

struct Particle {
private:
	glm::vec3 momentum;
public:
	glm::vec3 vel;
	glm::vec3 pos;
	float mass;
	float drag;
	void updateMassPreserveMomentum(float newMass) {
		updateMomentum();
		mass = newMass;
		vel = momentum / mass;
	}
	float * getMomentum() { updateMomentum(); return &momentum[0]; }
	void updateMomentum() {
		momentum = vel * mass;
	}
};