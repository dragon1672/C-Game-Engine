#pragma once

#include <Engine/IO/FileIO.h>
#include <Engine/Systems/Resources/Mesh.h>

namespace FileIO {
	Mesh loadFromBinary(fileByte * bytes,         std::string name = "");
	Mesh loadMeshFromFile(const char * filePath,  std::string name = "");
	Mesh loadMeshFromFile(std::string filePath,   std::string name = "");
}