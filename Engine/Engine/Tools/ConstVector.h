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
		currentIndex = 0;
	}
public:

	ConstVector() { init(47); }
	ConstVector(unsigned int startSize)    { init(startSize); }
	inline void add(const std::vector<T>& toAdd)        { add(&toAdd[0],toAdd.size()); }
	inline void add(const ConstVector<T>& toAdd)        { for (int i = 0; i < toAdd.size(); i++) add(toAdd[i]); }
	inline void add(const T * toAdd, unsigned int size) { for (int i = 0; i < size;         i++) add(toAdd[i]); }

	inline void push_back(const T& toAdd)				      { add(toAdd); }
	inline void push_back(const std::vector<T>& toAdd)        { add(toAdd); }
	inline void push_back(const ConstVector<T>& toAdd)        { add(toAdd); }
	inline void push_back(const T * toAdd, unsigned int size) { add(toAdd,size); }

	inline int find(T * toMatch) {
		for (uint i = 0; i < size(); i++)
			if(&(*this)[i] == toMatch) return i;
		return -1;
	}

	inline void add(const T& toAdd) {
		unsigned int a = currentIndex / startSize;
		unsigned int b = currentIndex % startSize;
		while(!(a < arrays.size() && b < startSize))
			arrays.push_back(new T[startSize]);
		arrays[a][b] = toAdd;
		currentIndex++;
	}
	inline T& get(int index)   { return (*this)[index]; }
	inline T& ConstVector<T>::first() { return (*this)[0]; }
	inline T& ConstVector<T>::last() { return (*this)[size()-1]; }
	inline void swap(int indexA, int indexB) {
		T& tmp = (*this)[indexA];
		(*this)[indexA] = (*this)[indexB];
		(*this)[indexB] = tmp;
	}
	inline bool remove(int index) {
		(*this)[index];
		while((unsigned)index < size()-1) {
			(*this)[index] = (*this)[index+1];
			index--;
		}
		return true;
	}

	inline void ConstVector<T>::pop_back() { if(currentIndex > 0) currentIndex--; }

	inline unsigned int size() { return currentIndex;   }
	inline const T& operator[](std::size_t idx) const { return const_cast<T&>(*this)[idx]; };

	inline T& operator[](std::size_t idx) {
		if(idx >= size())
			throw std::range_error("Out Of Bounds");//std::to_string(idx)+" is out of "+std::to_string(size())+" bounds");
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