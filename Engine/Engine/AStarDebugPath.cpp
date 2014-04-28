#include "AStarDebugPath.h"
#include <glm/gtx/transform.hpp>

void AStar::DEBUG::DebugPath::drawPath(DebugShapeManager& shapeManager, glm::vec3& currentPos) {
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

	for (int i = positions.size()-1; i >= 0 ; i--)
	{
		glm::mat4 posTransform = glm::translate(positions[i]);
		NodeRenderables.push_back(shapeManager.addUnitSphere(posTransform,glm::vec4(1,1,0,1)));
		if(i>0) {
			glm::vec3 leVec = positions[i-1] - positions[i];
			ConnectionRenderables.push_back(shapeManager.addUnitVector(positions[i], leVec,glm::vec4(0,0,1,1)));
		}
	}
}
glm::vec3 AStar::DEBUG::DebugPath::popCurrentConnection() {
	glm::vec3 ret = AStar::Path::popCurrentConnection();
	NodeRenderables.pop_back();
	return ret;
}