#pragma once

#include <vector>
#include "ParticleContact.h"
#include "Ray.h"
#include "unsigned.h"

class CollisionManager {
public:
	Ray * walls;
	uint numOfWalls;
	Particle * particles;
	uint numOfParticles;

	float restitution;

	void init(Ray * walls, uint numOfWalls, Particle * particles, uint numOfParticles, float restitution = 1) {
		this->walls = walls;
		this->numOfWalls = numOfWalls;
		this->particles = particles;
		this->numOfParticles = numOfParticles;
		this->restitution = restitution;
	}
	
	static bool eitherLengthZero(glm::vec3& a, glm::vec3& b) {
		return glm::dot(a,a) >= glm::dot(b,b) && glm::dot(b,b) > 0; // if either velocity is 0
	}

	static bool circleCollide(Particle * a, Particle * b) {
		glm::vec3 diff = a->pos - b->pos;
		float rads = a->mass/2 + b->mass/2;
		float lengthSquared = glm::dot(diff,diff);
		return lengthSquared < rads * rads;
	}
	bool collide(Particle * a, Particle * b, ParticleContact& outPram) {
		bool valid = circleCollide(a,b);
		if(valid) {
			glm::vec3 diff = a->pos - b->pos;
			float diffLength = glm::length(diff);
			glm::vec3 collisionNorm = diff / diffLength;
			float pen = (a->mass/2 + b->mass/2) - diffLength;

			outPram.particle[0] = a;
			outPram.particle[1] = b;
			outPram.contactNormal = collisionNorm;
			outPram.penetration = pen;
			outPram.restitution = restitution;
		}
		return valid;
	}
	bool collide(Particle * a, Ray * b, ParticleContact& outPram) {
		bool valid = false;
		glm::vec3 diff = a->pos - b->origin;
		glm::vec3 correctDiff = glm::proj(diff,b->direction);
		float lengthToPlane = glm::length(correctDiff);
		float rad = (a->mass/2);
		float pen = rad - glm::length(correctDiff);
		glm::vec3 vel = glm::proj(a->vel,b->direction);
		
		valid = pen >= 0;
		if(glm::dot(diff,b->direction) < 0) { // beyond wall
			pen = lengthToPlane + rad;
			valid = true;
		}
		if(valid) {
			outPram.particle[0] = a;
			outPram.particle[1] = nullptr;
			outPram.contactNormal = b->direction;
			outPram.penetration = pen;
			outPram.restitution = restitution;
		}
		return valid;
	}
	void update(float dt) {
		for (int i = 0; i < numOfParticles; i++)
		{
			particles[i].update(dt);
			for (int j = 0; j < numOfWalls; j++)
			{
				ParticleContact wallCollision;
				if(collide(&particles[i],&walls[j], wallCollision)) {
					wallCollision.collide(dt);
				}
			}
			for (int j = 0; j < numOfParticles; j++)
			{
				if(i!=j) {
					ParticleContact particleCollision;
					if(collide(&particles[i],&particles[j], particleCollision)) {
						particleCollision.collide(dt);
					}
				}
			}
		}
	}

	std::vector<ParticleContact> getCollisions() {
		std::vector<ParticleContact> ret;
		ParticleContact toAdd; // pushback copies data so lets only use one and update it
		for (uint i = 0; i < numOfParticles; i++)
		{
			for (uint j = 0; j < numOfWalls; j++)
			{
				Particle * a = &particles[i];
				Ray * b      = &walls[j];
				if(collide(a,b,toAdd)) {
					ret.push_back(toAdd);
				}
			}
			for (uint j = i; j < numOfParticles; j++)
			{
				Particle * a = &particles[i];
				Particle * b = &particles[j];
				if(i!=j && collide(a,b,toAdd)) {
					ret.push_back(toAdd);
				}
			}
		}
		return ret;
	}
	void makeItWork(float dt) {
		/*
		auto temp = getCollisions();
		for (int j = 0; j < temp.size(); j++)
		{
			// Find the contact with the largest closing velocity.
			float max = FLT_MAX;
			unsigned maxIndex = temp.size();
			for (int i = 0; i < temp.size(); i++)
			{
				float sepVel = temp[i].calculateSeparatingVelocity();
				if (sepVel < max && (sepVel < 0 || temp[i].penetration > 0))
				{
					max = sepVel;
					maxIndex = i;
				}
			}
			// Do we have anything worth resolving?
			if (maxIndex == temp.size()) break;
			// Resolve this contact.
			temp[maxIndex].collide(dt);
		}
		//*/
		/*
		for (int i = 0; i < 50; i++)
		{
			auto temp = getCollisions();
			for (uint j = 0; j < temp.size(); j++)
			{
				temp[j].collide(dt);
			}
			if(temp.size() > 0);
			else
				break;
		}
		//*/
		/*
		ParticleContact toAdd; // pushback copies data so lets only use one and update it
		for (uint i = 0; i < particles.size(); i++)
		{
			for (int a = 0; a < 1; a++)
			{
				for (uint j = 0; j < walls.size(); j++)
				{
					Particle * a = particles[i];
					Ray * b      = walls[j];
					if(collide(a,b,toAdd)) {
						toAdd.collide(dt);
					}
				}
				for (uint j = 0; j < particles.size(); j++)
				{
					Particle * a = particles[i];
					Particle * b = particles[j];
					if(i!=j && collide(a,b,toAdd)) {
						toAdd.collide(dt);
					}
				}
				for (uint j = 0; j < walls.size(); j++)
				{
					Particle * a = particles[i];
					Ray * b      = walls[j];
					if(collide(a,b,toAdd)) {
						toAdd.collide(dt);
					}
				}
			}
		}
		//*/
	}
};