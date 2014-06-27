#include <Engine\Tools\Random\Glm.h>
#include <random>
#include <glm\glm.hpp>

glm::vec3 Random::glmRand::randomUnitVector() {
	return glm::normalize(glm::vec3(randomFloat(-1,1),randomFloat(-1,1),randomFloat(-1,1)));
}
glm::vec3 Random::glmRand::randomFloatVectorInBoxRanged(float width, float height, float depth) {
	return glm::vec3(randomFloat(-width,width),randomFloat(-height,height),randomFloat(-depth,depth));
}
glm::vec3 Random::glmRand::randomFloatVectorInBox(float width, float height, float depth) {
	return glm::vec3(randomFloat(0,width),randomFloat(0,height),randomFloat(0,depth));
}
glm::vec3 Random::glmRand::randomIntVectorInBox(int   width, int   height, int depth) {
	return glm::vec3((float)randomInt(0,width),(float)randomInt(0,height),randomInt(0,depth));
}
glm::vec3 Random::glmRand::randomFloatVector(float low, float high) {
	return glm::vec3(randomFloat(low,high), randomFloat(low,high), randomFloat(low, high));
}
glm::vec3 Random::glmRand::randomIntVector(int   low, int   high) {
	return glm::vec3((float)randomInt(low,high), (float)randomInt(low,high), (float)randomInt(low,high));
}