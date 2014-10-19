#pragma once

#include <Engine/IO/FileIO.h>

namespace FileIO {
	Mesh loadMeshFromFile(const char * filePath);
	Mesh loadMeshFromFile(std::string filePath);
}