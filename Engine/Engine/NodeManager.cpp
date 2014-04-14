#include "NodeManager.h"
#include <glm/gtx/transform.hpp>



Node * NodeManager::getNextNode() {
	for (uint i = 0; i < numOfNodes; i++)
	{
		if(!nodes[i].isActive) {
			nodes[i].isActive = true;
			nodes[i].rednerable -> overrideColor = UnSelectedColor;
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
	for (uint i = 0; i < numOfNodes && ret == nullptr; i++)
	{
		if(nodes[i].isActive) {
			if(nodes[i].doesRayHit(click)) {
				ret = &nodes[i];
			}
		}
	}
	return ret;
}

void NodeManager::selectNode(Node * toSelect) {
	setAllConnections(false);
	setAllNodeColors(UnSelectedColor);
	currentSelectedNode = toSelect;
	currentSelectedNode->rednerable->overrideColor = SelectedColor;
	activateConnections(currentSelectedNode);
}
void NodeManager::deleteNode(Node * toDel) {
	//delete all connections
	for (uint i = 0; i < connections.size(); i++)
	{
		if(connections[i].from == toDel || connections[i].to == toDel) {
			connections[i].renderable->kill();
			connections[i].to -> rednerable -> overrideColor = UnSelectedColor;
			connections.erase(connections.begin() + i);
			i--;
		}
	}
	toDel->rednerable->draw = false;
	toDel->isActive = false;
}
void NodeManager::deleteNodeSelectedNode() {
	if(currentSelectedNode!=nullptr) {
		deleteNode(currentSelectedNode);
		setAllConnections(false);
		currentSelectedNode = nullptr;
	}
}
void NodeManager::setAllNodeColors(glm::vec4& colorToSet) {
	for (uint i = 0; i < numOfNodes; i++)
	{
		nodes[i].rednerable->overrideColor = colorToSet;
	}
}
void NodeManager::setAllConnections(bool state) {
	for (uint i = 0; i < connections.size(); i++)
	{
		connections[i].renderable->draw = state;
	}
}
void NodeManager::activateAllConnections() {
	for (uint i = 0; i < connections.size(); i++)
	{
		connections[i].renderable->draw = true;
		connections[i].to -> rednerable -> overrideColor = ConnectedNodeColor;
	}
}
void NodeManager::activateConnections(Node * startWith) {
	for (uint i = 0; i < connections.size(); i++)
	{
		if(connections[i].from == startWith) {
			connections[i].renderable->draw = true;
			connections[i].to -> rednerable -> overrideColor = ConnectedNodeColor;
		}
	}
}
void NodeManager::addOrSelectClick(Ray& click) {
	Node * selectedNode = getNodeClicked(click);
	if(selectedNode==nullptr) {
		addNodeOnPlane(click,glm::vec3(0,0,0),glm::vec3(0,1,0));
	} else {
		selectNode(selectedNode);
	}
}
void NodeManager::connectClick(Ray& click) {
	if(currentSelectedNode != nullptr) {
		Node * selectedNode = getNodeClicked(click);
		if(selectedNode!=nullptr && selectedNode != currentSelectedNode) {
			NodeConnection toAdd;
			toAdd.from = currentSelectedNode;
			toAdd.to = selectedNode;
			if(validConnections(toAdd)) {
				selectedNode->rednerable->overrideColor = ConnectedNodeColor;
				glm::vec3 vectorPointer = selectedNode->pos - currentSelectedNode->pos;
				toAdd.renderable = debugShapes->addUnitVector(currentSelectedNode->pos,vectorPointer,glm::vec4(0,1,1,1),1);
				connections.push_back(toAdd);
			}
		}
	}
}
bool NodeManager::validConnections(NodeConnection& toAdd) {
	bool valid = true;
	for (uint i = 0; i < connections.size() && valid; i++)
	{
		valid = (connections[i].from != toAdd.from || connections[i].to != toAdd.to);
	}
	return valid;
}