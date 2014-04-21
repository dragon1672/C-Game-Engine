#include "NodeManager.h"
#include <glm/gtx/transform.hpp>


EditorNode * NodeManager::getNextNode() {

	EditorNode * ret = new EditorNode;
	nodes.push_back(ret);
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
			EditorNode * temp = getNextNode();
			temp ->pos = positionToPlace;
			temp->rednerable->transform = glm::translate(positionToPlace);
		}
	}
}

EditorNode * NodeManager::getNodeClicked(Ray& click) {
	EditorNode * ret = nullptr;
	
	for (uint i = 0; i < nodes.size() && ret == nullptr; i++)
	{
		if(nodes[i]->doesRayHit(click)) {
			ret = nodes[i];
		}
	}
	return ret;
}

void NodeManager::selectNode(EditorNode * toSelect) {
	setAllConnections(false);
	setAllNodeColors(UnSelectedColor);
	currentSelectedNode = toSelect;
	currentSelectedNode->rednerable->overrideColor = SelectedColor;
	currentSelectedNode->activateConnections(ConnectedNodeColor);
}
void NodeManager::deleteNode(EditorNode * toDel) {
	//delete all connections
	numOfConnections -= toDel->shutdown();
	for (uint i = 0; i < nodes.size(); i++)
	{
		if(nodes[i] == toDel) {
			nodes.erase(nodes.begin() + i);
			break;
		}
	}

	for (uint i = 0; i < nodes.size(); i++)
	{
		numOfConnections -= nodes[i]->removeNode(toDel);
	}
	toDel->rednerable->draw = false;
	delete toDel;
}
void NodeManager::deleteNodeSelectedNode() {
	if(currentSelectedNode!=nullptr) {
		deleteNode(currentSelectedNode);
		setAllConnections(false);
		currentSelectedNode = nullptr;
		setAllNodeColors(UnSelectedColor);
	}
}
void NodeManager::deleteAll() {
	setAllConnections(false);
	currentSelectedNode = nullptr;
	setAllNodeColors(UnSelectedColor);
	while(nodes.size() > 0) {
		deleteNode(nodes[0]);
	}
}
void NodeManager::setAllNodeColors(glm::vec4& colorToSet) {
	for (uint i = 0; i < nodes.size(); i++)
	{
		nodes[i]->rednerable->overrideColor = colorToSet;
	}
}
void NodeManager::setAllConnections(bool state) {
	for (uint i = 0; i < nodes.size(); i++)
	{
		nodes[i]->setConnectionState(state);
	}
}
void NodeManager::activateAllConnections() {
	for (uint i = 0; i < nodes.size(); i++)
	{
		nodes[i]->activateConnections(ConnectedNodeColor);
	}
}
void NodeManager::addOrSelectClick(Ray& click) {
	EditorNode * selectedNode = getNodeClicked(click);
	if(selectedNode==nullptr) {
		addNodeOnPlane(click,glm::vec3(0,0,0),glm::vec3(0,1,0));
	} else {
		selectNode(selectedNode);
	}
}
void NodeManager::connectClick(Ray& click) {
	if(currentSelectedNode != nullptr) {
		EditorNode * selectedNode = getNodeClicked(click);
		if(currentSelectedNode->validConnection(selectedNode)) {
			EditorNodeConnection * toAdd = new EditorNodeConnection;
			toAdd->to = selectedNode;
			selectedNode->rednerable->overrideColor = ConnectedNodeColor;
			glm::vec3 vectorPointer = selectedNode->pos - currentSelectedNode->pos;
			toAdd->renderable = debugShapes->addUnitVector(currentSelectedNode->pos,vectorPointer,glm::vec4(0,1,1,1),1);
			currentSelectedNode->connections.push_back(toAdd);
			numOfConnections++;
		}
	}
}