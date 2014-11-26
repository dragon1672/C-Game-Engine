#include "FileIOWriting.h"
#include <fstream>



void FileIO::createDir(const char * dir)
{
	createDir(std::string(dir));
}

void FileIO::createDir(std::string dir)
{
	if(!validDir(dir)) {
		std::string makeADir = "mkdir "+ dir;
		system(makeADir.c_str());
	}
}

void FileIO::saveFile(FileData * toSave, std::string filePath)
{
	saveFile(toSave,filePath.c_str());
}

void FileIO::saveFile(FileData * toSave, const char * filePath)
{
	saveFile(toSave->data,toSave->size,filePath);
}

void FileIO::saveFile(fileByte * data, uint size, std::string pathAndName)
{
	saveFile(data,size,pathAndName.c_str());
}

void FileIO::saveFile(fileByte * data, uint size, const char * filePath)
{
	createDir(FileIO::extractFilePath(filePath));
	std::ofstream out(filePath, std::ios::binary );
	out.write(data,size);
	out.close();
}
