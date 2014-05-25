#pragma once

#include "Particle.h"
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
	glm::vec3 getVel(int index) const {
		return particle[index] != nullptr ? glm::proj(particle[index]->vel,contactNormal) : glm::vec3();
	}
	glm::vec3 getForce(int index) const {
		return particle[index] != nullptr ? glm::proj(particle[index]->totalForce,contactNormal) : glm::vec3();
	}
	float calculateSeparatingVelocity() const {
		glm::vec3 relativeVelocity = getVel(0) - getVel(1);
		float ret = glm::dot(relativeVelocity, contactNormal);
		return ret;
	}
	void resolveVelocity(float dt) {
		if(particle[1] != nullptr) particle[1]->totalForce -= getForce(1);
		float separatingVelocity = calculateSeparatingVelocity();
		float newSepVelocity = -separatingVelocity * restitution;
		
		//for resting collision
		glm::vec3 accCollision = particle[0]->getAcc() - ((particle[1]!=nullptr) ? particle[1]->getAcc() : glm::vec3());
		float projectedAcc = glm::dot(accCollision,contactNormal) * dt;
		if(projectedAcc < 0) {
			newSepVelocity += restitution * projectedAcc;
			newSepVelocity = MAX(newSepVelocity,0);
		}
		particle[0]->totalForce -= getForce(0);

		float deltaVelocity = newSepVelocity - separatingVelocity;
		float totalInverseMass = (1/particle[0]->mass);
		if (particle[1]!= nullptr) totalInverseMass += (1/particle[1]->mass);
		if (totalInverseMass <= 0) return;
		float impulse = deltaVelocity / totalInverseMass;
		glm::vec3 impulsePerIMass = contactNormal * impulse;
		particle[0]->vel += impulsePerIMass * (1/particle[0]->mass);
		if (particle[1] != nullptr) {
			particle[1]->vel += impulsePerIMass * -(1/particle[1]->mass);
		}
	}
};