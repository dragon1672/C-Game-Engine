#pragma once

#include <vector>
#include <string>
#include <ExportHeader.h>
#include <glm/glm.hpp>
#include <Engine/Tools/ConstVector.h>

class ENGINE_SHARED Stream {
	std::vector<char> buffer;
	int currentPos;
public:
	Stream() : currentPos(0) {};

	int CurrentPos() const { return currentPos; }
	void CurrentPos(int val) { currentPos = val; }

	void resetToBeg();
	void append(const void * d, int size);
	template<typename T> void append(T& d) {
		append(&d,sizeof(T));
	}
	template<typename T> void readAndMoveBack(T&d) {
		currentPos -= sizeof(T);
		d = *reinterpret_cast<T*>(&buffer[currentPos]);
	}
	template<typename T> void readAndMoveForward(T&d) {
		d = *reinterpret_cast<T*>(&buffer[currentPos]);
		currentPos += sizeof(T);
	}
	template<typename T> void readAndMoveForwardArray(T * array, int arraySize) {
		for (int i = 0; i < arraySize; i++) {
			readAndMoveForward(array[i]);
		}
	}
	template<typename T> friend Stream& operator<<(Stream& os, const T& obj) {
		os.append(obj);
		return os;
	}
	template<typename T> friend Stream& operator>>(Stream& os, T& obj) {
		os.readAndMoveForward(obj);
		return os;
	}
};


ENGINE_SHARED Stream& operator<<(Stream& os, const std::string& obj);
ENGINE_SHARED Stream& operator>>(Stream& os,       std::string& obj);

ENGINE_SHARED Stream& operator<<(Stream& os, const glm::vec4& obj);
ENGINE_SHARED Stream& operator>>(Stream& os,       glm::vec4& obj);
ENGINE_SHARED Stream& operator<<(Stream& os, const glm::vec3& obj);
ENGINE_SHARED Stream& operator>>(Stream& os,       glm::vec3& obj);
ENGINE_SHARED Stream& operator<<(Stream& os, const glm::vec2& obj);
ENGINE_SHARED Stream& operator>>(Stream& os,       glm::vec2& obj);

template<typename T>Stream& operator<<(Stream& os, const std::vector<T>& obj) {
	unsigned int size = obj.size();
	os << size;
	for (unsigned int i = 0; i < size; i++) {
		os << obj[i];
	}
	return os;
}
template<typename T>Stream& operator>>(Stream& os,       std::vector<T>& obj) {
	unsigned int size;
	os >> size;
	obj.clear();
	obj.resize(size);
	for (unsigned int i = 0; i < size; i++) {
		os >> obj[i];
	}
	return os;
}

template<typename T>Stream& operator<<(Stream& os, const ConstVector<T>& obj) {
	unsigned int size = obj.size();
	os >> size;
	for (unsigned int i = 0; i < size; i++) {
		os << obj[i];
	}
	return os;
}
template<typename T>Stream& operator>>(Stream& os,       ConstVector<T>& obj) {
	unsigned int size;
	os >> size;
	obj.clear();
	obj.resize(size);
	for (unsigned int i = 0; i < size; i++) {
		os >> obj[i];
	}
	return os;
}