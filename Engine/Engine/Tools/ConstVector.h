#pragma once

#include <vector>
#include <ExportHeader.h>

template<typename T> class ENGINE_SHARED ConstVector {
private:
	std::vector<T*> arrays;
	unsigned int startSize;
	unsigned int currentIndex;
	void init(int size);
public:
	ConstVector();
	ConstVector(unsigned int startSize);

	void add(std::vector<T> toAdd);
	void add(ConstVector<T> toAdd);
	void add(T * toAdd, unsigned int size);

	void add(T toAdd);
	T& get(int index);
	unsigned int size();
	const T& operator[](std::size_t idx) const;

	T& operator[](std::size_t idx);
	~ConstVector();
};