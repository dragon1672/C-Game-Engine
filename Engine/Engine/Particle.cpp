#include "Particle.h"

glm::vec3 Particle::resetTotalForceValue = glm::vec3();

void Particle::init(float drag, float mass) {
	this->drag = drag;
	this->mass = mass;
	totalForce = resetTotalForceValue;
}

//adds and resets total force
void Particle::addTotalForce(float dt) {
	vel += getAcc() * dt;
	totalForce = resetTotalForceValue;
}
glm::vec3 Particle::getAcc() {
	return totalForce / mass;
}
void Particle::update(float dt) {
	addTotalForce(dt);
	pos += vel * dt;
	vel *= pow(drag,dt); // drag!!
	momentum = vel * mass;
}