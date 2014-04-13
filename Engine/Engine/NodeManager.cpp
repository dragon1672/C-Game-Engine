#include "NodeManager.h"

glm::vec4 NodeManager::UnSelectedColor(0,0,1,1);
glm::vec4 NodeManager::SelectedColor(1,0,0,1);
glm::vec4 NodeManager::ConnectedNodeColor(0,1,0,1);




Node * NodeManager::getNextNode() {
	for (uint i = 0; i < numOfNodes; i++)
	{
		if(!nodes[i].isActive) {
			nodes[i].isActive = true;
			return &nodes[i];
		}
	}
	Node * ret = &nodes[numOfNodes++];
	ret->rednerable = debugShapes->addUnitCube(glm::mat4(),UnSelectedColor);
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
			getNextNode()->pos = positionToPlace;
		}
	}
}
NodeManager::NodeSelection NodeManager::getNodesSelected(Ray& click) {
	NodeSelection ret;
	ret.numOfNodes = 0;
	for(int i=0;i<numOfNodes;i++) {
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
	for (int i = 0; i < numOfNodes && ret != nullptr; i++)
	{
		if(nodes[i].isActive) {
			if(nodes[i].doesRayHit(click)) {
				ret = &nodes[i];
			}
		}
	}
	return ret;
}