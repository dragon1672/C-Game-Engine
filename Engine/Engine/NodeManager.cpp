#include "NodeManager.h"
#include <glm/gtx/transform.hpp>



Node * NodeManager::getNextNode() {
	for (uint i = 0; i < numOfNodes; i++)
	{
		if(!nodes[i].isActive) {
			nodes[i].isActive = true;
			return &nodes[i];
		}
	}
	Node * ret = &nodes[numOfNodes++];
	ret->rednerable = debugShapes->addUnitSphere(glm::mat4(),UnSelectedColor);
	ret->rednerable->enableOverrideColor = false;
	return ret;
}

void NodeManager::addNodeOnPlane(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm) {
	float denominator = glm::dot(ray.direction,planeNorm);
	if(denominator != 0)
	{
		glm::vec3 planePointToRayOrigin = planePos- ray.origin;
		float neumorator = glm::dot(planePointToRayOrigin, planeNorm);
		float distance = neumorator/denominator;
		if(distance >= 0) {
			glm::vec3 positionToPlace = ray.origin + ray.direction * distance;
			Node * temp = getNextNode();
			temp ->pos = positionToPlace;
			temp->rednerable->transform = glm::translate(positionToPlace);
		}
	}
}
NodeManager::NodeSelection NodeManager::getNodesSelected(Ray& click) {
	NodeSelection ret;
	ret.numOfNodes = 0;
	for(uint i=0;i<numOfNodes;i++) {
		if(nodes[i].isActive) {
			if(nodes[i].doesRayHit(click)) {
				ret.nodes[numOfNodes++] = &nodes[i];
			}
		}
	}
	return ret;
}

Node * NodeManager::getNodeClicked(Ray& click) {
	Node * ret = nullptr;
	for (uint i = 0; i < numOfNodes && ret != nullptr; i++)
	{
		if(nodes[i].isActive) {
			if(nodes[i].doesRayHit(click)) {
				ret = &nodes[i];
			}
		}
	}
	return ret;
}