#pragma once

#include "ParticleForceGenerator.h"
#include <vector>
#include "unsigned.h"

class ParticleForceRegistry {
	struct ParticleForcePair
	{
		Particle * particle;
		ParticleForceGenerator * forceGen;
	};
	std::vector<ParticleForcePair> pairs;
public:
	void add(Particle& particle, ParticleForceGenerator& forceGen) {
		add(&particle,&forceGen);
	}
	void add(Particle * particle, ParticleForceGenerator * forceGen) {
		ParticleForcePair toAdd = {particle,forceGen};
		pairs.push_back(toAdd);
	}
	void remove(Particle * particle, ParticleForceGenerator * forceGen) {
		for (uint i = 0; i < pairs.size(); i++)
		{
			if(pairs[i].forceGen == forceGen && pairs[i].particle == particle) {
				pairs.erase(pairs.begin() + i);
				return;
			}
		}
	}
	void clear() {
		pairs.clear();
	}
	void updateForces() {
		for (uint i = 0; i < pairs.size(); i++)
		{
			pairs[i].forceGen->updateForce(pairs[i].particle);
		}
	}
};