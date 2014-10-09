#pragma once

#include <vector>
#include <ExportHeader.h>

template<typename T> class ENGINE_SHARED ConstVector {
private:
	std::vector<T*> arrays;
	unsigned int startSize;
	unsigned int currentIndex;
	void init(int size) {
		startSize = size;
		arrays.push_back(new T[startSize]);
		currentIndex = 0;
	}
public:
	
	ConstVector() { init(47); }
	ConstVector(unsigned int startSize) { init(startSize); }

	void add(std::vector<T> toAdd)         { add(&toAdd[0],toAdd.size()); }
	void add(ConstVector<T> toAdd)      { for (int i = 0; i < toAdd.size(); i++) add(toAdd[i]); }
	void add(T * toAdd, unsigned int size) { for (int i = 0; i < size;         i++) add(toAdd[i]); }

	void add(T toAdd) {
		unsigned int a = currentIndex / startSize;
		unsigned int b = currentIndex % startSize;
		while(!(a < arrays.size() && b < startSize))
			arrays.push_back(new T[startSize]);
		arrays[a][b] = toAdd;
		currentIndex++;
	}
	T& get(int index)   { return (*this)[index]; }
	T& ConstVector<T>::first() { return (*this)[0]; }
	T& ConstVector<T>::last() { return (*this)[size()-1]; }

	void ConstVector<T>::pop_back() { if(currentIndex > 0) currentIndex--; }

	unsigned int size() { return currentIndex;   }
	const T& operator[](std::size_t idx) const { return const_cast<T&>(*this)[idx]; };

	T& operator[](std::size_t idx) {
		unsigned int a = idx / startSize;
		unsigned int b = idx % startSize;
		return arrays[a][b];
	};
	~ConstVector() {
		while(arrays.size() > 0) {
			int end = arrays.size() - 1;
			delete [] arrays[end];
			arrays.erase(arrays.begin() + end);
		}
	}
};