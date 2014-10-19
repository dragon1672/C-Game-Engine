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

	template<typename T>
	void myMemCopy(T * from, T * to, uint size) {
		int n = (size + 7) / 8;
		switch(size % 8) {
		case 0:
			do {	*to++ = *from++;
		case 7:		*to++ = *from++;
		case 6:		*to++ = *from++;
		case 5:		*to++ = *from++;
		case 4:		*to++ = *from++;
		case 3:		*to++ = *from++;
		case 2:		*to++ = *from++;
		case 1:		*to++ = *from++;
			} while(--n > 0);
		}
	}
}