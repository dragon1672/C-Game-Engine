#pragma once

#include <unordered_map>
#include "ParticleForceGenerator.h"
#include <vector>

class SpringForceGenerator : public ParticleForceGenerator {
public:
	std::unordered_map<Particle *,std::vector<glm::vec3 *>> springs;

	float springConstent;
	float springRestLength;

	void init(float springK, float restLength=1) {
		springConstent = springK;
		springRestLength = restLength;
	}

	void addSpring(Particle& leParticle, glm::vec3& anchor) {
		addSpring(&leParticle,anchor);
	}
	void addSpring(Particle * leParticle, glm::vec3& anchor) {
		auto id = springs.find(leParticle);
		if (id == springs.end()) {
			springs.emplace(leParticle,std::vector<glm::vec3*>());
		}
		springs[leParticle].push_back(&anchor);
	}
	void removeSpring(Particle& leParticle, glm::vec3& anchor) {
		removeSpring(&leParticle,&anchor);
	}
	void removeSpring(Particle * leParticle, glm::vec3 * anchor) {
		auto id = springs.find(leParticle);
		if (id != springs.end()) {
			std::vector<glm::vec3*>& data = springs[leParticle];
			for (int i = 0; i < data.size(); i++)
			{
				if(data[i] == anchor) {
					data.erase(data.begin() + i);
					i--;
				}
			}
			//wonder if this is worth it
			if(data.size() <= 0) {
				springs.erase(leParticle);
			}
		}
	}
	
	//override
	void updateForce(Particle * toUpdate) {
		auto id = springs.find(toUpdate);
		if (id != springs.end()) {
			std::vector<glm::vec3 *>& anchors = springs[toUpdate];
			for (int i = 0; i < anchors.size(); i++)
			{
				glm::vec3 anchor = *anchors[i];
				glm::vec3 diff = anchor - toUpdate->pos;
				float diffLength = glm::length(diff);
				float magnitude = springConstent * (diffLength - springRestLength);

				glm::vec3 springForce = (diff / diffLength) * magnitude;
				toUpdate->totalForce += springForce;
			}
		}
	}
};