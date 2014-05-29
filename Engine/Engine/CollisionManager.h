#pragma once

#include <vector>
#include "ParticleContact.h"
#include "Ray.h"
#include "unsigned.h"

class CollisionManager {
public:
	std::vector<Ray *> walls;
	std::vector<Particle *> particles;
	float restitution;
	
	bool eitherLengthZero(glm::vec3& a, glm::vec3& b) {
		return glm::dot(a,a) >= glm::dot(b,b) && glm::dot(b,b) > 0; // if either velocity is 0
	}

	bool circleCollide(Particle * a, Particle * b) {
		glm::vec3 diff = a->pos - b->pos;
		float rads = a->mass/2 + b->mass/2;
		float lengthSquared = glm::dot(diff,diff);
		return lengthSquared <= rads * rads;
	}
	bool collide(Particle * a, Particle * b, ParticleContact& outPram) {
		bool valid = false;
		if(circleCollide(a,b)) {
			glm::vec3 vels[2]; // used to store the projected velocities
			glm::vec3 diff = a->pos - b->pos;
			float diffLength = glm::length(diff);
			glm::vec3 collisionNorm = diff / diffLength;
			float pen = (a->mass/2 + b->mass/2) - diffLength;

			vels[0] = glm::proj(a->vel,collisionNorm);
			vels[1] = glm::proj(b->vel,collisionNorm);
			valid = true;//glm::dot(vels[0] - vels[1],collisionNorm) <= 0;
			if(valid || eitherLengthZero(vels[0],vels[1])) {
				outPram.particle[0] = a;
				outPram.particle[1] = b;
				outPram.contactNormal = collisionNorm;
				outPram.penetration = pen;
				outPram.restitution = restitution;
			}
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
		
		float temp = glm::dot(vel,b->direction);

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
	std::vector<ParticleContact> getWallCollisions() {
		std::vector<ParticleContact> ret;
		ParticleContact toAdd; // pushback copies data so lets only use one and update it
		for (uint i = 0; i < particles.size()/2; i++)
		{
			for (uint j = 0; j < walls.size(); j++)
			{
				Particle * a = particles[i];
				Ray * b      = walls[j];
				if(collide(a,b,toAdd)) {
					ret.push_back(toAdd);
				}
			}
		}
		return ret;
	}
	std::vector<ParticleContact> getParticleCollisions() {
		std::vector<ParticleContact> ret;
		ParticleContact toAdd; // pushback copies data so lets only use one and update it
		for (uint i = 0; i < particles.size()/2; i++)
		{
			for (uint j = 0; j < particles.size(); j++)
			{
				Particle * a = particles[i];
				Particle * b = particles[j];
				if(i!=j && collide(a,b,toAdd)) {
					ret.push_back(toAdd);
				}
			}
		}
		return ret;
	}
	std::vector<ParticleContact> getCollisions() {
		std::vector<ParticleContact> ret;
		ParticleContact toAdd; // pushback copies data so lets only use one and update it
		for (uint i = 0; i < particles.size(); i++)
		{
			for (uint j = 0; j < walls.size(); j++)
			{
				Particle * a = particles[i];
				Ray * b      = walls[j];
				if(collide(a,b,toAdd)) {
					ret.push_back(toAdd);
				}
			}
			for (uint j = i; j < particles.size(); j++)
			{
				Particle * a = particles[i];
				Particle * b = particles[j];
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
		//*
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