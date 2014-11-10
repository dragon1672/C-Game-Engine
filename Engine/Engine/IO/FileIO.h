#pragma once

#include <string>
#include <Engine/TypeDefs.h>

typedef char fileByte;

namespace FileIO {
	struct FileData {
		uint size;
		fileByte * data;
		bool ownsData;
		FileData() : size(0), data(nullptr), ownsData(true) {}
		inline void cleanup() { if(ownsData) delete [] data; }
	};
	std::string readFile(std::string filePath);
	std::string readFile(const char * filePath);
	FileData loadFile(std::string filePath);
	FileData loadFile(const char * filePath);
	bool validFile(std::string filePath);
	bool validFile(const char * filePath);

	template<typename T>
	void myMemCopy(T * from, T * to, uint size) {
		int n = (size + 30) / 31;
		switch(size % 31) {
		case 0:
			do {    	*to++ = *from++;
		case 30:		*to++ = *from++;
		case 29:		*to++ = *from++;
		case 28:		*to++ = *from++;
		case 27:		*to++ = *from++;
		case 26:		*to++ = *from++;
		case 25:		*to++ = *from++;
		case 24:		*to++ = *from++;
		case 23:		*to++ = *from++;
		case 22:		*to++ = *from++;
		case 21:		*to++ = *from++;
		case 20:		*to++ = *from++;
		case 19:		*to++ = *from++;
		case 18:		*to++ = *from++;
		case 17:		*to++ = *from++;
		case 16:		*to++ = *from++;
		case 15:		*to++ = *from++;
		case 14:		*to++ = *from++;
		case 13:		*to++ = *from++;
		case 12:		*to++ = *from++;
		case 11:		*to++ = *from++;
		case 10:		*to++ = *from++;
		case 9: 		*to++ = *from++;
		case 8: 		*to++ = *from++;
		case 7: 		*to++ = *from++;
		case 6: 		*to++ = *from++;
		case 5: 		*to++ = *from++;
		case 4: 		*to++ = *from++;
		case 3: 		*to++ = *from++;
		case 2: 		*to++ = *from++;
		case 1: 		*to++ = *from++;
			} while(--n > 0);
		}
	}
}