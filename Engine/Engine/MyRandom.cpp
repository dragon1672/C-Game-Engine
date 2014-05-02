#include "MyRandom.h"
#include <random>
#include <ctime>//for srand seed
#include "Vector 2.h"

std::random_device eng;
std::uniform_real_distribution<float> randF(0, 1);

int      Random::randomInt(int low, int high) {
	std::uniform_int_distribution<int> rand(low, high);
	return rand(eng);
}
float    Random::randomFloat(float low, float high) {
	return randomFloat() * (high-low) + low;
}
void     Random::init() {
	srand((unsigned)time(0));
}
int      Random::randomSign() {
	return (randomBool())? -1 : 1;
}
bool     Random::randomBool() {
	return (randomInt(0,1)==0);
}
float    Random::randomFloat() {
	return randF(eng);
}
Vector2D Random::randomUnitVector() {
	return Vector2D(randomFloat(-1,1),randomFloat(-1,1)).normalized();
}
Vector2D Random::randomFloatVectorInBox(float width, float height) {
	return Vector2D(randomFloat(0,width),randomFloat(0,height));
}
Vector2D Random::randomIntVectorInBox(int   width, int   height) {
	return Vector2D((float)randomInt(0,width),(float)randomInt(0,height));
}
Vector2D Random::randomFloatVector(float low, float high) {
	return Vector2D(randomFloat(low,high),randomFloat(low,high));
}
Vector2D Random::randomIntVector(int   low, int   high) {
	return Vector2D((float)randomInt(low,high),(float)randomInt(low,high));
}
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