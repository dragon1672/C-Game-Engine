#pragma once

#include <map>
#include "ParticleForceGenerator.h"
#include <vector>
#include "unsigned.h"

class SpringForceGenerator : public ParticleForceGenerator {
	struct Spring {
		float springRestLength;
		glm::vec3 * anchor;
	};
	struct SpringConnections {
		std::vector<Spring> springs;
	};
public:
	std::map<Particle *,SpringConnections> springs;

	float springConstent;
	float springRestLength;

	void init(float springK, float restLength=1) {
		springConstent = springK;
		springRestLength = restLength;
	}

	void addSpring(Particle& leParticle, glm::vec3& anchor, float overrideRestlength = -1) {
		addSpring(&leParticle,anchor,overrideRestlength);
	}
	void addSpring(Particle * leParticle, glm::vec3& anchor, float overrideRestlength = -1) {
		auto id = springs.find(leParticle);
		if (id == springs.end()) {
			springs.emplace(leParticle,SpringConnections());
		}
		Spring toAdd = { overrideRestlength, &anchor };
		springs[leParticle].springs.push_back(toAdd);
	}
	void removeSpring(Particle& leParticle, glm::vec3& anchor) {
		removeSpring(&leParticle,&anchor);
	}
	void removeSpring(Particle * leParticle, glm::vec3 * anchor) {
		auto id = springs.find(leParticle);
		if (id != springs.end()) {
			auto& data = springs[leParticle].springs;
			for (uint i = 0; i < data.size(); i++)
			{
				if(data[i].anchor == anchor) {
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
			auto& anchors = springs[toUpdate].springs;
			for (uint i = 0; i < anchors.size(); i++)
			{
				float springRestLength = (anchors[i].springRestLength < 0) ? this->springRestLength : anchors[i].springRestLength;
				glm::vec3 anchor = *anchors[i].anchor;
				glm::vec3 diff = anchor - toUpdate->pos;
				float diffLength = glm::length(diff);
				float magnitude = springConstent * (diffLength - springRestLength);

				glm::vec3 springForce = (diff / diffLength) * magnitude;
				toUpdate->totalForce += springForce;
			}
		}
	}
};