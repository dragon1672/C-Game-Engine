#pragma once

#include <string>
#include <Engine/unsigned.h>
#include <Engine/Renderer/Geo/Mesh.h>

typedef char fileByte;

namespace FileIO {
	struct FileData {
		uint size;
		fileByte * data;
		inline void cleanup() { delete [] data; }
	};
	std::string readFile(const char * filePath);
	FileData loadFile(const char * filePath);
	bool validFile(const char * filePath);
}