#include <Engine\Tools\Random\Glm.h>
#include <random>
#include <glm\glm.hpp>

glm::vec3 Random::glmRand::UnitVector() {
	return glm::normalize(glm::vec3(Float(-1,1),Float(-1,1),Float(-1,1)));
}
glm::vec3 Random::glmRand::FloatVectorInBoxRanged(float width, float height, float depth) {
	return glm::vec3(Float(-width,width),Float(-height,height),Float(-depth,depth));
}
glm::vec3 Random::glmRand::FloatVectorInBox(float width, float height, float depth) {
	return glm::vec3(Float(0,width),Float(0,height),Float(0,depth));
}
glm::vec3 Random::glmRand::IntVectorInBox(int   width, int   height, int depth) {
	return glm::vec3((float)Int(0,width),(float)Int(0,height),Int(0,depth));
}
glm::vec3 Random::glmRand::FloatVector(float low, float high) {
	return glm::vec3(Float(low,high), Float(low,high), Float(low, high));
}
glm::vec3 Random::glmRand::IntVector(int   low, int   high) {
	return glm::vec3((float)Int(low,high), (float)Int(low,high), (float)Int(low,high));
}