#pragma once

#include "Particle.h"
#include <glm\gtx\projection.hpp>

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
		glm::vec3 particleMovement[2];
		if (penetration <= 0) return;
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
	float calculateSeparatingVelocity() const {
		glm::vec3 relativeVelocity = getVel(0) - getVel(1);
		float ret = glm::dot(relativeVelocity, contactNormal);
		return ret;
	}
	void resolveVelocity(float dt) {
		float separatingVelocity = calculateSeparatingVelocity();
		float newSepVelocity = -separatingVelocity * restitution;
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