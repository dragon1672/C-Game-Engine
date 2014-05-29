#include "Particle.h"

glm::vec3 Particle::resetTotalForceValue = glm::vec3();

void Particle::init(float drag, float mass) {
	this->drag = drag;
	this->mass = mass;
	totalForce = resetTotalForceValue;
}

glm::vec3 Particle::getAcc() {
	return totalForce / mass;
}
void Particle::addForce(glm::vec3& toAdd) {
	totalForce += toAdd;
}
void Particle::addAcc(glm::vec3& toAdd) {
	totalForce += toAdd * mass;
}
void Particle::clearForce() {
	totalForce = resetTotalForceValue;
}

void Particle::update(float dt) {
	vel += getAcc() * dt;
	pos += vel * dt;
	vel *= (drag != 1) ? pow(drag,dt) : 1; // drag!!
	momentum = vel * mass;
}