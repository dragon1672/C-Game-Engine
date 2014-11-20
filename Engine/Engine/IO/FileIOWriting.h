#pragma once

#include <Engine/IO/FileIO.h>

namespace FileIO {
	void createDir(std::string  dir);
	void createDir(const char * dir);
	void saveFile(FileData * toSafe, std::string  pathAndName);
	void saveFile(FileData * toSafe, const char * pathAndName);
	void saveFile(fileByte * data, uint size, const char * pathAndName);
	void saveFile(fileByte * data, uint size, std::string pathAndName);
}