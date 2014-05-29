#pragma once

#include "CollisionEngine.h"
#include "Particle.h"
#include <glm/gtx/projection.hpp>
#include "ExportHeader.h"

class ENGINE_SHARED CollisionMassCircles : public CollisionEngine {
public:
	Particle* particles[2];
	glm::vec3 vels[2];
	glm::vec3 collisionNorm;
	float pen;

	void init(Particle * p1, Particle* p2) {
		particles[0] = p1;
		particles[1] = p2;
	}
	void update() {
		glm::vec3 diff = particles[0]->pos - particles[1]->pos;
		float diffLength = glm::length(diff);
		collisionNorm = diff / diffLength;
		pen = (particles[0]->mass/2 + particles[1]->mass/2) - diffLength;
		vels[0] = glm::proj(particles[0]->vel,collisionNorm);
		vels[1] = glm::proj(particles[1]->vel,collisionNorm);
	}
	bool hasCollided() {
		return circleCollide(particles[0]->pos,particles[0]->mass/2,particles[1]->pos,particles[1]->mass/2)
			&& glm::dot(vels[0] - vels[1],collisionNorm) <= 0;
	}
	float getPenetration() {
		return pen;
	}
	glm::vec3 getNormal() {
		return collisionNorm;
	}
	bool circleCollide(glm::vec3& object1Pos, float object1Rad, glm::vec3& object2Pos, float object2Rad) {
		glm::vec3 diff = object1Pos - object2Pos;
		float rads = object1Rad + object2Rad;
		return glm::dot(diff,diff) < rads * rads;
	}
};