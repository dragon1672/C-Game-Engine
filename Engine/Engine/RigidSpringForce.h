#pragma once

#include <map>
#include "ParticleForceGenerator.h"
#include <vector>
#include "unsigned.h"
#include "RidgidBody.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/perpendicular.hpp>

class SpringForceGenerator {
	struct Spring {
		float springRestLength;
		glm::vec3 offset;
		glm::vec3 * anchor;
	};
	struct SpringConnections {
		std::vector<Spring> springs;
	};
public:
	std::map<RidgidBody *,SpringConnections> springs;

	float springConstent;
	float springRestLength;

	void init(float springK, float restLength=1) {
		springConstent = springK;
		springRestLength = restLength;
	}

	void addSpring(RidgidBody& leParticle, glm::vec3 offset, glm::vec3& anchor, float overrideRestlength = -1) {
		addSpring(&leParticle,offset, anchor,overrideRestlength);
	}
	void addSpring(RidgidBody * leParticle, glm::vec3 offset, glm::vec3& anchor, float overrideRestlength = -1) {
		auto id = springs.find(leParticle);
		if (id == springs.end()) {
			springs.emplace(leParticle,SpringConnections());
		}
		Spring toAdd = { overrideRestlength, offset, &anchor };
		springs[leParticle].springs.push_back(toAdd);
	}
	void clear() {
		springs.clear();
	}
	void removeSpring(RidgidBody& leParticle, glm::vec3& anchor) {
		removeSpring(&leParticle,&anchor);
	}
	void removeSpring(RidgidBody * leParticle, glm::vec3 * anchor) {
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
	void updateForce(RidgidBody * toUpdate) {
		auto id = springs.find(toUpdate);
		if (id != springs.end()) {
			auto& anchors = springs[toUpdate].springs;
			for (uint i = 0; i < anchors.size(); i++)
			{
				glm::vec3 rotatedOffset = glm::rotate(anchors[i].offset, toUpdate->rotation, glm::vec3(0,0,1));
				glm::vec3 realPos = toUpdate->core.pos + rotatedOffset;
				float springRestLength = (anchors[i].springRestLength < 0) ? this->springRestLength : anchors[i].springRestLength;
				glm::vec3 anchor = *anchors[i].anchor;
				glm::vec3 diff = anchor - realPos;
				if(glm::dot(diff,diff) > 0) {
					float diffLength = glm::length(diff);
					float magnitude = springConstent * (diffLength - springRestLength);

					glm::vec3 springForce = (diff / diffLength) * magnitude;
					toUpdate->core.totalForce += springForce;

					//angle vel
					glm::vec3 lever = rotatedOffset;
					glm::vec3 leverForce = springForce;
					glm::vec3 leverPerpForce = glm::perp(leverForce, glm::normalize(lever));
					glm::vec3 totalTorque = glm::cross(lever, leverPerpForce);
					toUpdate->totalTorque += totalTorque;
				}
			}
		}
	}
};