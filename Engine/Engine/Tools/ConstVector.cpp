#include "ConstVector.h"

template<typename T> void ConstVector::init(int size) {
	startSize = size;
	arrays.push_back(new T[startSize]);
	currentIndex = 0;
}
template<typename T> ConstVector::ConstVector() { init(47); }
template<typename T> ConstVector::ConstVector(unsigned int startSize) { init(startSize); }

template<typename T> void ConstVector::add(std::vector<T> toAdd)         { add(&toAdd[0],toAdd.size()); }
template<typename T> void ConstVector::add(ConstVector<T> toAdd)      { for (int i = 0; i < toAdd.size(); i++) add(toAdd[i]); }
template<typename T> void ConstVector::add(T * toAdd, unsigned int size) { for (int i = 0; i < size;         i++) add(toAdd[i]); }

template<typename T> void ConstVector::add(T toAdd) {
	unsigned int a = currentIndex / startSize;
	unsigned int b = currentIndex % startSize;
	while(!(a < arrays.size() && b < startSize))
		arrays.push_back(new T[startSize]);
	arrays[a][b] = toAdd;
	currentIndex++;
}
template<typename T> T& ConstVector::get(int index)   { return (*this)[index]; }
template<typename T> unsigned int ConstVector::size() { return currentIndex;   }
template<typename T> const T& ConstVector::operator[](std::size_t idx) const { return const_cast<T&>(*this)[idx]; };

template<typename T> T& ConstVector::operator[](std::size_t idx) {
	unsigned int a = idx / startSize;
	unsigned int b = idx % startSize;
	return arrays[a][b];
};
template<typename T> ConstVector::~ConstVector() {
	while(arrays.size() > 0) {
		int end = arrays.size() - 1;
		delete [] arrays[end];
		arrays.erase(arrays.begin() + end);
	}
}