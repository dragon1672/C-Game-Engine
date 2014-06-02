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

	void init(Particle * particles, uint numOfParticles, Ray * walls, uint numOfWalls, float restitution = 1) {
		this->particles = particles;
		this->numOfParticles = numOfParticles;
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

		collisionManager.update(dt);
	}
	float& getRestitution() { return collisionManager.restitution; }
};