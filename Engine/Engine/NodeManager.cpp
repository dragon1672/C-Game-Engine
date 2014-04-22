#include "NodeManager.h"
#include <glm/gtx/transform.hpp>


EditorNode * NodeManager::getNextNode() {

	EditorNode * ret = new EditorNode;
	nodes.push_back(ret);
	ret->rednerable = debugShapes->addUnitSphere(glm::mat4(),UnSelectedColor);
	ret->rednerable->enableOverrideColor = false;
	return ret;
}

int NodeManager::getNodeId(EditorNode * toFind) {
	for (uint i = 0; i < nodes.size(); i++)
	{
		if(nodes[i] == toFind) return i;
	}
	return -1;
}
void NodeManager::addNode(glm::vec3 pos) {
	EditorNode * temp = getNextNode();
	temp ->pos = pos;
	temp->rednerable->transform = glm::translate(pos);
}
void NodeManager::addNodeOnPlane(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm) {
	float denominator = glm::dot(ray.direction,planeNorm);
	if(denominator != 0)
	{
		glm::vec3 planePointToRayOrigin = planePos- ray.origin;
		float neumorator = glm::dot(planePointToRayOrigin, planeNorm);
		float distance = neumorator/denominator;
		if(distance >= 0) {
			addNode(ray.origin + ray.direction * distance);
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
		addNodeOnPlane(click,glm::vec3(0,.25,0),glm::vec3(0,1,0));
	} else {
		selectNode(selectedNode);
	}
}
void NodeManager::connectClick(Ray& click) {
	if(currentSelectedNode != nullptr) {
		EditorNode * selectedNode = getNodeClicked(click);
		if(currentSelectedNode->validConnection(selectedNode)) {
			addConnection(currentSelectedNode,selectedNode);
		}
	}
}
void NodeManager::addConnection(uint fromID, uint toID) {
	EditorNode * fromNode = nodes[fromID];
	EditorNode * toNode = nodes[toID];
	addConnection(fromNode, toNode);
}
void NodeManager::addConnection(EditorNode * fromNode, EditorNode * toNode) {
	EditorNodeConnection * toAdd = new EditorNodeConnection;
	toAdd->to = toNode;
	toAdd->cost = glm::length(toNode->pos - fromNode->pos);
	toNode->rednerable->overrideColor = ConnectedNodeColor;
	glm::vec3 vectorPointer = toNode->pos - fromNode->pos;
	toAdd->renderable = debugShapes->addUnitVector(fromNode->pos,vectorPointer,glm::vec4(0,1,1,1),1);
	fromNode->connections.push_back(toAdd);
	numOfConnections++;
}
void NodeManager::importNodesAndConnections(GameNode * gameNodes, uint nodeCount) {
	deleteAll();
	for (uint i = 0; i < nodeCount; i++)
	{
		addNode(gameNodes->pos);
	}
	for (uint i = 0; i < nodeCount; i++)
	{
		for (uint j = 0; j < gameNodes[i].numOfConnections; j++)
		{
			uint fromID = i;
			GameNode currentNode = gameNodes[i];
			GameNodeConnection currentCOnnection = currentNode.connections[j];
			GameNode * dest = currentCOnnection.to;
			uint toID = gameNodes[i].connections[j].to - gameNodes;
			addConnection(fromID,toID);
		}
	}
}