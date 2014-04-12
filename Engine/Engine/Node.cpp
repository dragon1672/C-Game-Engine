#include "Node.h"


bool Node::doesRayHit(Ray& ray) {
	glm::vec3 raytoCircle = pos - ray.origin;
	glm::vec3 rayExtended = glm::proj(raytoCircle,ray.direction);

	float raytoCircleLength = glm::dot(pos,pos); // returns length squared
	float rayExtendedLength = glm::dot(rayExtended,rayExtended); // returns length squared
	float collisionLength = raytoCircleLength - rayExtendedLength;

	return collisionLength < radius * radius;
}
bool Node::tryIntersectionVector(Ray& ray, glm::vec3& ret) {
	glm::vec3 raytoCircle = pos - ray.origin;
	glm::vec3 rayExtended = glm::proj(raytoCircle,ray.direction);

	float raytoCircleLengthSquared = glm::dot(pos,pos); // returns length squared
	float rayExtendedLengthSquared = glm::dot(rayExtended,rayExtended); // returns length squared
	float collisionLengthSquared = raytoCircleLengthSquared - rayExtendedLengthSquared;
	float radiusLengthSquared = radius*radius;

	if(radiusLengthSquared > collisionLengthSquared) {
		ret = rayExtended - (sqrt(radiusLengthSquared - collisionLengthSquared))*(ray.direction);
		return true;
	}
	return false;
}