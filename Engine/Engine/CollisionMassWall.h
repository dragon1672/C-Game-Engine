#pragma once

#include "CollisionEngine.h"
#include "Particle.h"
#include <glm/gtx/projection.hpp>
#include "ExportHeader.h"
#include "Ray.h"

class ENGINE_SHARED CollisionMassWall: public CollisionEngine {
public:
	Particle* particle;
	Ray * wall;

	glm::vec3 vel;
	float pen;

	void init(Particle * p1, Ray * wall) {
		particle = p1;
		this->wall = wall;
	}
	void update() {
		glm::vec3 diff = particle->pos - wall->origin;
		glm::vec3 correctDiff = glm::proj(diff,wall->direction);
		float lengthToPlane = glm::length(correctDiff);
		float rad = (particle->mass/2);
		pen = rad - lengthToPlane;
		vel = glm::proj(particle->vel,wall->direction);
	}
	bool hasCollided() {
		return pen >= 0
			&& glm::dot(vel,wall->direction) <=0;
	}
	float getPenetration() {
		return pen;
	}
	glm::vec3 getNormal() {
		return wall->direction;
	}
}; 