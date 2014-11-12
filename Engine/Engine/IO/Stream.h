#pragma once

#include <vector>
#include <string>
#include <ExportHeader.h>
#include <glm/glm.hpp>
#include <Engine/Tools/ConstVector.h>
#include <Engine/IO/StreamableObject.h>
#include <Engine/IO/FileIO.h>


#pragma region HelperDefines

#define STREAMER_FOR_TYPE(prefix,friend,type)\
	prefix friend Stream& operator<<(Stream& os, const type& obj) { os.append(obj);             return os; } \
	prefix friend Stream& operator>>(Stream& os,       type& obj) { os.readAndMoveForward(obj); return os; }
#define STREAMER_FOR_SIGNED_UNSIGNED_TYPE(prefix,friend,type)\
	STREAMER_FOR_TYPE(prefix,friend,type); \
	STREAMER_FOR_TYPE(prefix,friend,unsigned type);

#pragma endregion

class ENGINE_SHARED Stream {
	std::vector<char> buffer;
	int currentPos;
	
	void internalAppend(const void * d, int size);
public:
	int CurrentPos() const;
	void CurrentPos(int val);

	Stream();;

	void resetToBeg();
	template<typename T> void append(T*array,int count) {
		internalAppend(array,sizeof(T)*count);
	}
	template<typename T> void append(T& d) {
		append(&d,1);
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
		FileIO::myMemCopy((T*)&buffer[currentPos],array,arraySize);
		currentPos += arraySize*sizeof(T);
	}



	void exportToFile(const char * filePath);
	void importFromFile(const char * filePath);


	ENGINE_SHARED friend Stream& operator<<(Stream& os, StreamableObject& obj);
	ENGINE_SHARED friend Stream& operator>>(Stream& os, StreamableObject& obj);
	ENGINE_SHARED friend Stream& operator<<(Stream& os, StreamableObject * obj);
	ENGINE_SHARED friend Stream& operator>>(Stream& os, StreamableObject * obj);

	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,float);
	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,double);
	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,bool);
	STREAMER_FOR_SIGNED_UNSIGNED_TYPE(ENGINE_SHARED,friend,int);
	STREAMER_FOR_SIGNED_UNSIGNED_TYPE(ENGINE_SHARED,friend,long);
	STREAMER_FOR_SIGNED_UNSIGNED_TYPE(ENGINE_SHARED,friend,short);
	STREAMER_FOR_SIGNED_UNSIGNED_TYPE(ENGINE_SHARED,friend,char);

	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,glm::vec2);
	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,glm::vec3);
	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,glm::vec4);
	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,glm::mat2);
	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,glm::mat3);
	STREAMER_FOR_TYPE(ENGINE_SHARED,friend,glm::mat4);


	ENGINE_SHARED friend Stream& operator<<(Stream& os, const std::string& obj);
	ENGINE_SHARED friend Stream& operator>>(Stream& os, std::string& obj);



};

template<typename T> Stream& operator<<(Stream& os, std::vector<T>& obj) {
	unsigned int size = obj.size();
	os << size;
	for (unsigned int i = 0; i < size; i++) {
		os << obj[i];
	}
	return os;
}
template<typename T> Stream& operator>>(Stream& os, std::vector<T>& obj) {
	unsigned int size;
	os >> size;
	obj.resize(size);
	for (unsigned int i = 0; i < size; i++) {
		os >> obj[i];
	}
	return os;
}
template<typename T> Stream& operator<<(Stream& os, ConstVector<T>& obj) {
	unsigned int size = obj.size();
	os << size;
	for (unsigned int i = 0; i < size; i++) {
		os << obj[i];
	}
	return os;
}
template<typename T> Stream& operator>>(Stream& os, ConstVector<T>& obj) {
	unsigned int size;
	os >> size;
	obj.resize(size);
	for (unsigned int i = 0; i < size; i++) {
		os >> obj[i];
	}
	return os;
}