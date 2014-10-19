#pragma once

#include <Engine/IO/FileIO.h>
#include <Engine/Systems/Resources/Mesh.h>

namespace FileIO {
	Mesh loadFromBinary(fileByte * bytes, const char * name = nullptr);
	Mesh loadMeshFromFile(const char * filePath, const char * name = nullptr);
	Mesh loadMeshFromFile(std::string filePath, const char * name = nullptr);
}