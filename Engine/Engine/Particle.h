#pragma once

#include <glm/glm.hpp>

struct Particle {
public:
	glm::vec3 vel;
	glm::vec3 pos;
	glm::vec3 momentum;
	float mass;
	float drag;
	bool conserveMomentum;
	float acc;

	void init(float acceleration, float drag, float mass=1, bool conserveMomentum=false) {
		this->acc = acceleration;
		this->drag = drag;
		this->mass = mass;
		this->conserveMomentum = conserveMomentum;
	}

	void update(glm::vec3& accDir, float dt) {
		if(conserveMomentum) {
			vel = momentum / mass;
		}
		vel += accDir * acc * dt;
		vel *= drag;
		momentum = vel * mass;
		pos += vel * dt;
	}
};