#include "NodeManager.h"
#include <glm/gtx/transform.hpp>

#define RIC_BYTE(a) reinterpret_cast<char*>(&a), sizeof(a)
#define RIC(type,value) reinterpret_cast<type>(value)

EditorNode * NodeManager::getNextNode() {

	EditorNode * ret = new EditorNode;
	nodes.push_back(ret);
	ret->rednerable = debugShapes->addUnitSphere(glm::mat4(),UnSelectedColor);
	ret->rednerable->enableOverrideColor = false;
	return ret;
}
uint NodeManager::getOffset(GameNode* startOfArray) {
	static int offset = 0;
	if(startOfArray[offset].pos != nodes[0]->pos) {
		for (int i = 1; i < nodes.size(); i++)
		{
			offset = i;
			if(startOfArray[offset].pos != nodes[0]->pos) return offset;
		}
		offset = -1;
	}
	return offset;
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
glm::vec3 NodeManager::rayPlaneIntersection(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm) {
	float denominator = glm::dot(ray.direction,planeNorm);
	if(denominator != 0)
	{
		glm::vec3 planePointToRayOrigin = planePos- ray.origin;
		float neumorator = glm::dot(planePointToRayOrigin, planeNorm);
		float distance = neumorator/denominator;
		if(distance >= 0) {
			return (ray.origin + ray.direction * distance);
		}
	}
	return glm::vec3();
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
EditorNode * NodeManager::findNode(GameNode * toFind, GameNode * startOfArray) {
	int index = toFind - startOfArray;
	int offset = getOffset(startOfArray);
	if(nodes[offset + index]->pos == toFind->pos) {
		return nodes[offset + index];
	} else {
		return findNode(toFind);
	}
}
EditorNode * NodeManager::findNode(GameNode* toFind) {
	for(uint i=0; i<nodes.size(); i++) {
		if(nodes[i]->pos == toFind->pos)
			return nodes[i];
	}
	return nullptr;
}
EditorNode * NodeManager::findNode(glm::vec3& pos) {
	for(uint i=0; i<nodes.size(); i++) {
		if(nodes[i]->pos == pos)
			return nodes[i];
	}
	return nullptr;
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
void NodeManager::setAllVisability(bool state) {
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i]->setConnectionState(state);
		nodes[i]->rednerable->draw = state;
	}
}
void NodeManager::show() {
	setAllVisability(true);
}

void NodeManager::hide() {
	setAllVisability(false);
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
		int existingConnectionID = currentSelectedNode->getConnectionId(selectedNode);
		if(selectedNode!=nullptr) {
			if(existingConnectionID < 0) {
				addConnection(currentSelectedNode,selectedNode);
			} else {
				currentSelectedNode->deleteConnection(existingConnectionID);
				selectedNode->rednerable->overrideColor = UnSelectedColor;
			}
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

void NodeManager::hilightPath(AStar::Path& lePath,glm::vec4& nextNodeColor, glm::vec4& finalNodeColor, glm::vec4& pathNodeColor) {

	EditorNode * firstNode = findNode(lePath.currentDestination);
	firstNode->rednerable->overrideColor = nextNodeColor;
	for (int i = lePath.positions.size()-1; i >= 0; i--)
	{
		EditorNode * currentNode = findNode(lePath.positions[i]);
		currentNode->rednerable->overrideColor = pathNodeColor;
		if(i>0) {
			glm::vec3& nextPos = lePath.positions[i-1];
			currentNode->activateConnection(nextPos,pathNodeColor);
		}
	}
	EditorNode * lastNode = findNode(lePath.positions[0]);
	firstNode->rednerable->overrideColor = finalNodeColor;
}

void NodeManager::importNodesAndConnections(GameNode * gameNodes, uint nodeCount) {
	int indexOffset = nodes.size();
	//requires 2 sets because all nodes have to exist to make connections
	//Since nodes are all pointers and created by "new" the pointer can't be calculated before they are created :(
	for (uint i = 0; i < nodeCount; i++)
	{
		addNode(gameNodes[i].pos);
	}
	for (uint i = 0; i < nodeCount; i++)
	{
		for (uint j = 0; j < gameNodes[i].numOfConnections; j++)
		{
			uint fromID = i + indexOffset;
			uint toID = gameNodes[i].connections[j].to - gameNodes + indexOffset;
			addConnection(fromID,toID);
		}
	}
	setAllConnections(false);
	//activateAllConnections();
}
GameNode * NodeManager::exportToGameNode(int& numOfNodes) {
	numOfNodes = nodes.size();
	int fileSize = nodes.size() * sizeof(GameNode);
	int connectionOffset = fileSize;
	fileSize += numOfConnections * sizeof(GameNodeConnection);

	char * buffer = new char[fileSize];
	GameNode * ret = reinterpret_cast<GameNode *>(buffer);
	GameNodeConnection * connections = reinterpret_cast<GameNodeConnection *>(buffer + connectionOffset);

	int currentConnectionOffset = 0;

	for (uint i = 0; i < nodes.size(); i++)
	{
		ret[i].pos = nodes[i]->pos;
		ret[i].numOfConnections = nodes[i]->connections.size();
		ret[i].connections = &connections[currentConnectionOffset];

		for (uint j = 0; j < nodes[i]->connections.size(); j++) // adding connection data
		{
			connections[currentConnectionOffset].cost = nodes[i]->connections[j]->cost;
			
			int id = getNodeId(nodes[i]->connections[j]->to);
			connections[currentConnectionOffset].to = &ret[id];
			currentConnectionOffset++;
		}
	}
	return ret;
}