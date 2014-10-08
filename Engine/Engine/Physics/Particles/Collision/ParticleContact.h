#pragma once

#include <Engine\Physics\Particles\Particle.h>
#include <glm\gtx\projection.hpp>

#define MAX(a,b) ( a < b ? b : a)

class ParticleContact
{
public:
	Particle* particle[2];
	float restitution;
	glm::vec3 contactNormal;
	float penetration;

	void collide(float dt) {
		resolve(dt);
	}
	void resolve(float dt) {
		resolveVelocity(dt);
		resolveInterpenetration(dt);
	}
	void resolveInterpenetration(float dt) {
		if (penetration <= 0) return;
		glm::vec3 particleMovement[2];
		float totalInverseMass = 1/particle[0]->mass;
		if (particle[1]) totalInverseMass += (1/particle[1]->mass);
		if (totalInverseMass <= 0) return;
		glm::vec3 movePerIMass = contactNormal * (penetration / totalInverseMass);
		particleMovement[0] = movePerIMass * (1/particle[0]->mass);
		if (particle[1] != nullptr) {
			particleMovement[1] = movePerIMass * -particle[1]->mass;
			particle[1]->pos += particleMovement[1];
		} else {
			particleMovement[1] = glm::vec3();
		}
		particle[0]->pos += particleMovement[0];
	}
	float getSign(float val) const {
		return (val < 0)? -1 : 1;
	}
	glm::vec3 getVel(int index) const {
		return particle[index] != nullptr ? glm::proj(particle[index]->vel,contactNormal) : glm::vec3();
	}
	glm::vec3 getForce(int index) const {
		return particle[index] != nullptr ? glm::proj(particle[index]->totalForce,contactNormal) : glm::vec3();
	}
	glm::vec3 getAcc(int index) {
		return particle[index] != nullptr ? particle[index]->getAcc() : glm::vec3();
	}
	float calculateSeparatingVelocity() const {
		glm::vec3 relativeVelocity = getVel(0) - getVel(1);
		float ret = glm::dot(relativeVelocity, contactNormal);
		return ret;
	}
	void resolveVelocity(float dt) {
		float separatingVelocity = calculateSeparatingVelocity();

		if(particle[1]==nullptr) { // colliding with wall
			particle[0]->addForce(getForce(0));
		}
		
		if(separatingVelocity > 0) return;
		float newSepVelocity = -separatingVelocity * restitution;

		//for resting collision
		glm::vec3 accCollision = getAcc(0) - getAcc(1);
		float accCausedSepVelocity = glm::dot(accCollision, contactNormal) * dt;
		if(accCausedSepVelocity < 0) {
			newSepVelocity += restitution * accCausedSepVelocity;
			if(newSepVelocity < 0) {
				newSepVelocity = 0;
			}
		}
		float deltaVelocity = newSepVelocity - separatingVelocity;

		float totalInverseMass = particle[0]->getInverseMass();
		if (particle[1]!= nullptr) totalInverseMass += particle[1]->getInverseMass();
		if (totalInverseMass <= 0) return;
		float impulse = deltaVelocity / totalInverseMass;
		glm::vec3 impulsePerIMass = contactNormal * impulse;
		particle[0]->vel += impulsePerIMass * particle[0]->getInverseMass();
		if (particle[1] != nullptr) {
			particle[1]->vel += impulsePerIMass * - particle[1]->getInverseMass();
		}
	}
};