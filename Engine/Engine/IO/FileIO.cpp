#include "FileIO.h"
#include <fstream>
#include <cassert>
#include <Engine/Tools/Printer.h>
#include <dirent.h>

namespace FileIO {
	std::string readFile(std::string filePath) {
		return readFile(filePath.c_str());
	}
	std::string readFile(const char * filePath) {
		std::ifstream file(filePath);
		return std::string(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
	}
	FileData loadFile(std::string filePath) {
		return loadFile(filePath.c_str());
	}
	FileData loadFile(const char * filePath) {
		FileData ret;
		//understand da file
		std::ifstream input( filePath , std::ios::binary | std::ios::in);
		if(!input.good()) {
			printErr(100) "Find not found at ", filePath;
			return FileData();
		}
		assert(input.good()); 
		input.seekg(0, std::ios::end);
		ret.size = (int)input.tellg();
		input.seekg(0, std::ios::beg);

		//copy da file
		ret.data = new fileByte[ret.size];
		input.read(ret.data, ret.size);
		input.close();

		return ret;
	}
	bool validFile(std::string filePath) {
		return validFile(filePath.c_str());
	}
	bool validFile(const char * filePath) {
		std::ifstream file(filePath);
		bool valid = file.good();
		file.close();
		return valid;
	}

	std::vector<std::string> filesInDir(std::string dir)
	{
		std::vector< std::string > files;
		DIR *dp;
		struct dirent *dirp;
		if((dp  = opendir(dir.c_str())) == NULL) {
			printErr(100) "Error(", errno, ") opening ", dir;
			return std::vector<std::string>();
		}
		while ((dirp = readdir(dp)) != NULL) {
			if (validFile(dir+"/"+dirp->d_name)) {
				files.push_back(dirp->d_name);
			}
		}
		closedir(dp);
		return files;
	}
	std::vector<std::string> foldersInDir(std::string dir)
	{
		std::vector< std::string > files;
		DIR *dp;
		struct dirent *dirp;
		if((dp  = opendir(dir.c_str())) == NULL)
		{
			printErr(100) "Error(", errno, ") opening ", dir;
			return std::vector<std::string>();
		}
		while ((dirp = readdir(dp)) != NULL) {
			if (std::string(dirp->d_name) != "." && validDir(dir+"/"+dirp->d_name)) {
				files.push_back(dirp->d_name);
			}
		}
		closedir(dp);
		return files;
	}
	bool validDir(std::string dir)
	{
		DIR *dp;
		if((dp  = opendir(dir.c_str())) == NULL) {
			closedir(dp);
			return false;
		}
		closedir(dp);
		return true;
	}

}