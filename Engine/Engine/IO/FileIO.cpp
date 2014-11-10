#include "FileIO.h"
#include <fstream>
#include <cassert>
#include <Engine/Tools/Printer.h>

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
}