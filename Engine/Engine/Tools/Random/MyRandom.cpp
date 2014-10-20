#include <Engine\Tools\Random\MyRandom.h>
#include <random>

std::random_device eng;
std::uniform_real_distribution<float> randF(0, 1);

int      Random::Int(int low, int high) {
	std::uniform_int_distribution<int> rand(low, high);
	return rand(eng);
}
float    Random::Float(float low, float high) {
	return Float() * (high-low) + low;
}
int      Random::Sign() {
	return (Bool())? -1 : 1;
}
bool     Random::Bool(int weightFalse) {
	return (Int(0,weightFalse)==0);
}
float    Random::Float() {
	return randF(eng);
}