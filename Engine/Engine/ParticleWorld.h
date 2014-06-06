#pragma once

#include "unsigned.h"
#include "CollisionManager.h"
#include "ParticleForceRegistry.h"

class ParticleWorld {
public:
	Particle * particles;
	uint numOfParticles;
	ParticleForceRegistry forceReg;
	CollisionManager collisionManager;
	bool collision;

	void init(Particle * particles, uint numOfParticles, Ray * walls, uint numOfWalls, float restitution = 1, bool collision = true) {
		this->particles = particles;
		this->numOfParticles = numOfParticles;
		this->collision = collision;
		collisionManager.init(walls,numOfWalls,particles,numOfParticles,restitution);
	}
	void addForce(uint particleIndex, ParticleForceGenerator * forceGen) {
		addForce(&particles[particleIndex], forceGen);
	}
	void addForce(Particle * leParticle, ParticleForceGenerator * forceGen) {
		forceReg.add(leParticle, forceGen);
	}
	void update(float dt) {
		forceReg.updateForces();

		if(collision) {
			collisionManager.update(dt);
		} else {
			for (uint i = 0; i < numOfParticles; i++)
			{
				particles[i].update(dt);
			}
		}
	}
	float& getRestitution() { return collisionManager.restitution; }
};