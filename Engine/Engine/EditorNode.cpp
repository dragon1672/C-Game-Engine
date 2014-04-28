#include "EditorNode.h"
#include "EditorNodeConnection.h"

int  EditorNode::shutdown() {
	int connectionsDeleted = connections.size();
	while(connections.size()>0) {
		connections[0]->renderable->kill();
		delete connections[0];
		connections.erase(connections.begin() + 0);
	}
	rednerable->kill();
	return connectionsDeleted;
}
int  EditorNode::removeNode(EditorNode * idtoRemove) {
	int connectionsDeleted = 0;
	for (uint i = 0; i < connections.size(); i++)
	{
		if(connections[i]->to == idtoRemove) { // remove the connection
			deleteConnection(i);
			connectionsDeleted++;
			i--;
		}
	}
	return connectionsDeleted;
}
void EditorNode::activateConnections(glm::vec4& color) {
	for (uint i = 0; i < connections.size(); i++)
	{
		connections[i] -> renderable->draw = true;
		connections[i] -> to -> rednerable -> overrideColor = color;
	}
}
void EditorNode::activateConnection(glm::vec3& nodePos, glm::vec4& color) {
	for (uint i = 0; i < connections.size(); i++)
	{
		if(connections[i] -> to -> pos == nodePos) {
			connections[i] -> renderable->draw = true;
			connections[i] -> to -> rednerable -> overrideColor = color;
			return; // we are done here
		}
	}
}

bool EditorNode::validConnection(EditorNode * toConnect) {
	bool valid = (toConnect != this) && (toConnect != nullptr);
	for (uint i = 0; i < connections.size() && valid; i++)
	{
		valid = connections[i]->to != toConnect;
	}
	return valid;
}

int EditorNode::getConnectionId(EditorNode * toConnect) {
	for (uint i = 0; i < connections.size(); i++)
	{
		if(connections[i]->to == toConnect) return i;
			
	}
	return -1;
}

void EditorNode::deleteConnection(uint id) {
	connections[id]->renderable->kill();
	delete connections[id];
	connections.erase(connections.begin() + id);
}

void EditorNode::setConnectionState(bool state) {
	for (uint i = 0; i < connections.size(); i++)
	{
		connections[i]->renderable->draw = state;
	}
}
bool EditorNode::doesRayHit(Ray& ray) {
	glm::vec3 raytoCircle_C = pos - ray.origin;
	glm::vec3 rayExtended_A = glm::proj(raytoCircle_C,ray.direction);

	float raytoCircleLength = glm::dot(raytoCircle_C,raytoCircle_C); // returns length squared
	float rayExtendedLength = glm::dot(rayExtended_A,rayExtended_A); // returns length squared
	float collisionLength = raytoCircleLength - rayExtendedLength;

	return collisionLength < radius * radius;
}
bool EditorNode::tryIntersectionVector(Ray& ray, glm::vec3& ret) {
	glm::vec3 raytoCircle = pos - ray.origin;
	glm::vec3 rayExtended = glm::proj(raytoCircle,ray.direction);

	float raytoCircleLengthSquared = glm::dot(raytoCircle,raytoCircle); // returns length squared
	float rayExtendedLengthSquared = glm::dot(rayExtended,rayExtended); // returns length squared
	float collisionLengthSquared = raytoCircleLengthSquared - rayExtendedLengthSquared;
	float radiusLengthSquared = radius*radius;

	if(radiusLengthSquared > collisionLengthSquared) {
		ret = rayExtended - (sqrt(radiusLengthSquared - collisionLengthSquared))*(ray.direction);
		return true;
	}
	return false;
}