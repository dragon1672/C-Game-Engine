#pragma once

#include <glm/glm.hpp>
#include <math.h>

struct Particle {
public:
	glm::vec3 vel;
	glm::vec3 pos;
	glm::vec3 momentum;
	float mass;
	float drag;
	glm::vec3 totalForce; // reset and calculated each tick from forces registered
	std::vector<glm::vec3 *> allForces;

	void init(float drag, float mass=1) {
		this->drag = drag;
		this->mass = mass;
	}

	//adds and resets total force
	void addTotalForce(float dt) {
		glm::vec3 acc = totalForce / mass;
		vel += acc * dt;
		totalForce = glm::vec3();
	}
	void update(float dt) {
		addTotalForce(dt);
		pos += vel * dt;
		vel *= pow(drag,dt); // drag!!
		momentum = vel * mass;
	}
};