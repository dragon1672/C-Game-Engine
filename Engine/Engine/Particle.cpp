#include "Particle.h"

glm::vec3 Particle::resetTotalForceValue = glm::vec3();

void Particle::init(float drag, float mass) {
	this->drag = drag;
	this->mass = mass;
	totalForce = resetTotalForceValue;
}

//adds and resets total force
void Particle::addTotalForce(float dt) {
	glm::vec3 acc = totalForce / mass;
	vel += acc * dt;
	totalForce = resetTotalForceValue;
}
void Particle::update(float dt) {
	addTotalForce(dt);
	pos += vel * dt;
	vel *= pow(drag,dt); // drag!!
	momentum = vel * mass;
}