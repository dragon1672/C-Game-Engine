#include <Engine\Tools\Random\MyRandom.h>
#include <random>

std::random_device eng;
std::uniform_real_distribution<float> randF(0, 1);

int      Random::randomInt(int low, int high) {
	std::uniform_int_distribution<int> rand(low, high);
	return rand(eng);
}
float    Random::randomFloat(float low, float high) {
	return randomFloat() * (high-low) + low;
}
int      Random::randomSign() {
	return (randomBool())? -1 : 1;
}
bool     Random::randomBool(int weightFalse) {
	return (randomInt(0,weightFalse)==0);
}
float    Random::randomFloat() {
	return randF(eng);
}