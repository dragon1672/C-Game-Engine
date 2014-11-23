#include "Stream.h"
#include <Engine/TypeDefs.h>
#include <fstream>
#include <Engine/IO/FileIOWriting.h>



void Stream::exportToFile(const char * filePath)
{
	auto data = &(*buffer)[0];
	uint size  = (*buffer).size();
	FileIO::saveFile(data,size,filePath);
}

void Stream::importFromFile(const char * filePath)
{
	std::ifstream input( filePath , std::ios::binary | std::ios::in);
	assert(input.good()); 
	input.seekg(0, std::ios::end);
	int sizeResult = (int)input.tellg();
	input.seekg(0, std::ios::beg);
	(*buffer).resize(sizeResult);
	input.read(&(*buffer)[0], sizeResult);
	input.close();
	currentPos = 0;
}

void Stream::resetToBeg()
{
	currentPos = 0;
}

void Stream::CurrentPos(int val)
{
	currentPos = val;
}

int Stream::CurrentPos() const
{
	return currentPos;
}

Stream::Stream() : currentPos(0), buffer(new std::vector<char>())
{
	
}

Stream& operator<<(Stream& os, const std::string& obj)
{
	unsigned int size = obj.length();
	os << size;
	for (unsigned int i = 0; i < size; i++) {
		os << obj[i];
	}
	return os;
}

Stream& operator<<(Stream& os, StreamableObject& obj)
{
	obj.Save(os);
	return os;
}

Stream& operator>>(Stream& os, std::string& obj)
{
	unsigned int size;
	os >> size;
	obj = std::string(size,' ');
	for (unsigned int i = 0; i < size; i++) {
		os >> obj[i];
	}
	return os;
}

Stream& operator>>(Stream& os, StreamableObject& obj)
{
	obj.Load(os);
	return os;
}

void Stream::internalAppend(const void * d, int size)
{
	char * data = (char*)d;
	(*buffer).resize((*buffer).size()+size);
	FileIO::myMemCopy(data,&(*buffer)[currentPos],size);
	currentPos += size;
}

void Stream::Save(Stream&s)
{
	s.append(&(*buffer)[currentPos],buffer->size()-currentPos);
}

void Stream::Load(Stream&s)
{
	readAndMoveForwardArray(&(*s.buffer)[s.currentPos],s.buffer->size()-s.currentPos);
}
