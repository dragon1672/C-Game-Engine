#pragma once

#include "AStarPath.h"
#include "AStarDebugPath.h"
#include "Renderer.h"
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "State.h"
#include "AStarDebugPathGenerator.h"
#include "ExportHeader.h"
#include "Flag.h"

class ENGINE_SHARED Character {
private:
	//FetchingFlagState fetchFlagState;
	//RunningToHomeBaseState runToHomeBaseState;
	AStar::PathGenerator * pather;
	DebugShapeManager * shaper;
public:
	AStar::DEBUG::DebugPath path;
	glm::mat4 * transformMat;
	float speed;
	glm::vec3 pos;
	glm::vec3 direction;
	glm::vec3 finalDestination;
	glm::vec3 currentDestination;
	
	Flag * meFlag;
	glm::vec3 homeBasePos;

	bool hasFlag;
	State myState;
private:
	void prepForNextDest();
	void reset();
public:
	Character() {
		hasFlag = false;
		meFlag = nullptr;
		transformMat = nullptr;
	}
	void init(glm::mat4 * transformMat, Flag* meFlagOfAwesome, glm::vec3 homeBasePos, AStar::PathGenerator& pather, DebugShapeManager& shaper);

	void changePath(AStar::Path& newOne);

	void setNewDestPos(glm::vec3& newPos);
	void newFlagPos(glm::vec3 newPos);

	void update(float dt);
	glm::mat4x4 getWorld2View();
};