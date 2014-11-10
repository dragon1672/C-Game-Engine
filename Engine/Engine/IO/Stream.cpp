#include "Stream.h"
#include <Engine/TypeDefs.h>



void Stream::resetToBeg()
{
	currentPos = 0;
}

void Stream::append(const void * d, int size)
{
	char * data = (char*)d;
	buffer.resize(buffer.size()+size);
	for (int i = 0; i < size; i++) {
		buffer[currentPos++] = data[i];
	}
}

Stream& operator<<(Stream& os, const std::string& obj)
{
	unsigned int size = obj.length();
	os.append(size);
	for (unsigned int i = 0; i < size; i++) {
		os << obj[i];
	}
	return os;
}

Stream& operator<<(Stream& os, const glm::vec4& obj)
{
	os << obj.x << obj.y << obj.z << obj.a;
	return os;
}

Stream& operator<<(Stream& os, const glm::vec3& obj)
{
	os << obj.x << obj.y << obj.z;
	return os;
}

Stream& operator<<(Stream& os, const glm::vec2& obj)
{
	os << obj.x << obj.y;
	return os;
}


Stream& operator>>(Stream& os, std::string& obj)
{
	unsigned int size;
	os.readAndMoveForward(size);
	obj = std::string(size,' ');
	for (unsigned int i = 0; i < size; i++) {
		os.readAndMoveForward(obj[i]);
	}
	return os;
}


Stream& operator>>(Stream& os, glm::vec4& obj)
{
	os >> obj.r >> obj.g >> obj.b >> obj.a;
	return os;
}

Stream& operator>>(Stream& os, glm::vec3& obj)
{
	os >> obj.x >> obj.y >> obj.z;
	return os;
}

Stream& operator>>(Stream& os, glm::vec2& obj)
{
	os >> obj.x >> obj.y;
	return os;
}
