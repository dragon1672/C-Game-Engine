#pragma once

#include "Particle.h"

class ParticleContact
{
public:
	Particle* particle[2];
	float restitution;
	glm::vec3 contactNormal;
	float penetration;
	void resolve(float dt) {
		resolveVelocity(dt);
		resolveInterpenetration(dt);
	}
	void resolveInterpenetration(float dt) {
		glm::vec3 particleMovement[2];
		// If we don’t have any penetration, skip this step.
		if (penetration <= 0) return;
		// The movement of each object is based on their inverse mass,
		// so total that.
		float totalInverseMass = 1/particle[0]->mass;
		if (particle[1]) totalInverseMass += (1/particle[1]->mass);
		// If all particles have infinite mass, then we do nothing.
		if (totalInverseMass <= 0) return;
		// Find the amount of penetration resolution per unit
		// of inverse mass.
		glm::vec3 movePerIMass = contactNormal * (penetration / totalInverseMass);
		// Calculate the movement amounts.
		particleMovement[0] = movePerIMass * (1/particle[0]->mass);
		if (particle[1] != nullptr) {
			particleMovement[1] = movePerIMass * -particle[1]->mass;
			particle[1]->pos += particleMovement[1];
		} else {
			particleMovement[1] = glm::vec3();
		}
		// Apply the penetration resolution.
		particle[0]->pos += particleMovement[0];
	}

	float calculateSeparatingVelocity() const {
		glm::vec3 relativeVelocity = particle[0]->vel;

		if (particle[1]) relativeVelocity -= particle[1]->vel;

		float ret = glm::dot(relativeVelocity, contactNormal);
		return ret;
	}
private:
	void resolveVelocity(float dt) {
		// Find the velocity in the direction of the contact.
		float separatingVelocity = calculateSeparatingVelocity();
		// Check if it needs to be resolved.
		if (separatingVelocity > 0) {
			// The contact is either separating, or stationary;
			// no impulse is required.
			return;
		}
		// Calculate the new separating velocity.
		float newSepVelocity = -separatingVelocity * restitution;
		float deltaVelocity = newSepVelocity - separatingVelocity;
		// We apply the change in velocity to each object in proportion to
		// their inverse mass (i.e., those with lower inverse mass [higher
		// actual mass] get less change in velocity).
		float totalInverseMass = (1/particle[0]->mass);
		if (particle[1]!= nullptr) totalInverseMass += (1/particle[1]->mass);
		// If all particles have infinite mass, then impulses have no effect.
		if (totalInverseMass <= 0) return;
		// Calculate the impulse to apply.
		float impulse = deltaVelocity / totalInverseMass;
		// Find the amount of impulse per unit of inverse mass.
		glm::vec3 impulsePerIMass = contactNormal * impulse;
		// Apply impulses: they are applied in the direction of the contact,
		// and are proportional to the inverse mass.
		particle[0]->vel += impulsePerIMass * (1/particle[0]->mass);

		if (particle[1] != nullptr) {
			// Particle 1 goes in the opposite direction
			particle[1]->vel += impulsePerIMass * -(1/particle[1]->mass);
		}
	}
};