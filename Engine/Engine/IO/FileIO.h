#pragma once

#include <string>
#include <Engine/TypeDefs.h>

typedef char fileByte;

namespace FileIO {
	struct FileData {
		uint size;
		fileByte * data;
		inline void cleanup() { delete [] data; }
	};
	std::string readFile(std::string filePath);
	std::string readFile(const char * filePath);
	FileData loadFile(std::string filePath);
	FileData loadFile(const char * filePath);
	bool validFile(std::string filePath);
	bool validFile(const char * filePath);
}