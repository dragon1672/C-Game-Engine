#include "AStarDebugPath.h"
#include <glm/gtx/transform.hpp>

#define CURRENT_NODE_COLOR glm::vec4(1,1,0,1)
#define FINAL_NODE_COLOR glm::vec4(0,1,0,1)
#define PATH_NODE_COLOR glm::vec4(1,0,0,1)
#define LINE_COLOR  glm::vec4(1,1,1,1)

void AStar::DEBUG::DebugPath::drawPath(DebugShapeManager& shapeManager) {
	if(currentNodeRenderable == nullptr) {
		currentNodeRenderable = shapeManager.addUnitSphere(glm::translate(currentDestination),CURRENT_NODE_COLOR,false);
	}
	for (int i = 0; i < NodeRenderables.size(); i++)
	{
		NodeRenderables[i]->kill();
	}
	NodeRenderables.clear();
	for (int i = 0; i < ConnectionRenderables.size(); i++)
	{
		ConnectionRenderables[i]->kill();
	}
	ConnectionRenderables.clear();

	for (int i=0; i < positions.size(); i++)
	{
		glm::mat4 posTransform = glm::translate(positions[i]);
		NodeRenderables.push_back(shapeManager.addUnitSphere(posTransform,PATH_NODE_COLOR,false));
		if(i < positions.size()-1) {
			glm::vec3 leVec = positions[i] - positions[i+1];
			ConnectionRenderables.push_back(shapeManager.addUnitVector(positions[i+1],leVec,LINE_COLOR,false));
		}
	}
	if(NodeRenderables.size() > 0) {
		NodeRenderables[0]->overrideColor = FINAL_NODE_COLOR;
	}
	if(positions.size() > 0) {
		glm::vec3 leVec = positions[positions.size()-1] - currentDestination;
		ConnectionRenderables.push_back(shapeManager.addUnitVector(currentDestination,leVec,LINE_COLOR,false));
	}
	currentNodeRenderable->transform = glm::translate(currentDestination);
}
glm::vec3 AStar::DEBUG::DebugPath::popCurrentConnection() {
	glm::vec3 ret = AStar::Path::popCurrentConnection();
	if(NodeRenderables.size() > 0) {
		int id = NodeRenderables.size() - 1;
		NodeRenderables[id]->kill();
		NodeRenderables.pop_back();
	}
	if(ConnectionRenderables.size() > 0) {
		int id = ConnectionRenderables.size() - 1;
		ConnectionRenderables[id]->kill();
		ConnectionRenderables.pop_back();
	}
	currentNodeRenderable->transform = glm::translate(currentDestination);

	return ret;
}
void AStar::DEBUG::DebugPath::setVisability(bool newState) {
	if(currentNodeRenderable != nullptr) {
		currentNodeRenderable->draw = newState;
	}
	for (int i = 0; i < NodeRenderables.size(); i++)
	{
		NodeRenderables[i]->draw = newState;
	}
	for (int i = 0; i < ConnectionRenderables.size(); i++)
	{
		ConnectionRenderables[i]->draw = newState;
	}
}