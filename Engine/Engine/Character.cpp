#include "Character.h"


void Character::prepForNextDest() {
	if(myState == State::FetchingFlagState && pos == meFlag->pos) {
		myState = State::RunningToHomeBaseState;
		setNewDestPos(homeBasePos);
		hasFlag = true;
		meFlag->holder = this;
	} else if(myState==State::RunningToHomeBaseState && pos == homeBasePos) {
		myState = State::FetchingFlagState;
		changePath(pather->getPath(pos,meFlag->pos));
		finalDestination = meFlag->pos;
		hasFlag = false;
		meFlag->holder = nullptr;
	} else {
		currentDestination = path.popCurrentConnection();
		direction = glm::normalize(currentDestination - pos);
	}
}
void Character::init(glm::mat4 * transformMat, Flag* meFlagOfAwesome, glm::vec3 homeBasePos, AStar::PathGenerator& pather, DebugShapeManager& shaper) {
	this->shaper = &shaper;
	this->pather = &pather;
	this->homeBasePos = homeBasePos;
	this->transformMat = transformMat;
	this->meFlag = meFlagOfAwesome;
	myState = State::FetchingFlagState;
	speed = 10;
}
void Character::reset() {
	if(myState == State::RunningToHomeBaseState) {
		setNewDestPos(homeBasePos);
		hasFlag = true;
		meFlag->holder = this;
	} else if(myState==State::FetchingFlagState) {
		changePath(pather->getPath(pos,meFlag->pos));
		finalDestination = meFlag->pos;
		hasFlag = false;
		meFlag->holder = nullptr;
	}
}
void Character::changePath(AStar::Path& newOne) {
	path.load(newOne);
	currentDestination = path.popCurrentConnection();
	path.drawPath(*shaper);
}
void Character::setNewDestPos(glm::vec3& newPos) {
	changePath(pather->getPath(pos,newPos));
	prepForNextDest();
	finalDestination = newPos;
}
void Character::newFlagPos(glm::vec3 newPos) {
	if(myState == State::FetchingFlagState) {
		setNewDestPos(newPos);
	}
}
void Character::update(float dt) {
	if(meFlag->hasChangedPos()) {
		newFlagPos(meFlag->pos);
	}

	glm::vec3 path2Dest = currentDestination - pos;
	glm::vec3 movement = direction * speed * dt;
	if(glm::dot(path2Dest,path2Dest) <= glm::dot(movement,movement)) { // destination will be reached within the tick
		pos = currentDestination;
		prepForNextDest();
	} else {
		pos += movement;
	}
	if(hasFlag) {
		meFlag->pos = pos + glm::vec3(0,3,0);
	}
	(*transformMat) = glm::translate(pos+ glm::vec3(0,3,0)) * glm::orientation(direction,glm::vec3(1,0,0));
}
glm::mat4x4 Character::getWorld2View() {
	glm::vec3 pos = this->pos;
	pos+=glm::vec3(0,7,0) + 4.0f * direction;
	return glm::lookAt(pos,pos-direction,glm::vec3(0,1,0));
}