#include <Engine\Tools\Random\MyMath.h>
#include <random>

Vector2D Random::myRand::randomUnitVector() {
	return Vector2D(randomFloat(-1,1),randomFloat(-1,1)).normalized();
}
Vector2D Random::myRand::randomFloatVectorInBox(float width, float height) {
	return Vector2D(randomFloat(0,width),randomFloat(0,height));
}
Vector2D Random::myRand::randomIntVectorInBox(int   width, int   height) {
	return Vector2D((float)randomInt(0,width),(float)randomInt(0,height));
}
Vector2D Random::myRand::randomFloatVector(float low, float high) {
	return Vector2D(randomFloat(low,high),randomFloat(low,high));
}
Vector2D Random::myRand::randomIntVector(int   low, int   high) {
	return Vector2D((float)randomInt(low,high),(float)randomInt(low,high));
}