#pragma once

#include <string>
#include <Engine/TypeDefs.h>
#include <vector>
#include <ExportHeader.h>
#include <windows.h>

typedef char fileByte;

namespace FileIO {
	struct ENGINE_SHARED FileData {
		SYSTEMTIME creationTime,
			lpLastAccessTime,
			lastWriteTime;
		void initFileTimes(const char * filePath);
		void initFileTimes(const std::wstring filePath);
		void initFileTimes(const std::string filePath);
		void initFileTimes(const wchar_t * filePath);

		void initFromFile(const char * filePath);
		uint size;
		fileByte * data;
		bool ownsData;
		FileData();
		void cleanup();
	};
	ENGINE_SHARED std::string readFile2String(std::string filePath);
	ENGINE_SHARED std::string readFile2String(const char * filePath);
	ENGINE_SHARED FileData loadFile(std::string filePath);
	ENGINE_SHARED FileData loadFile(const char * filePath);
	ENGINE_SHARED bool validFile(std::string filePath);
	ENGINE_SHARED bool validFile(const char * filePath);

	ENGINE_SHARED std::vector<std::string> filesInDir(std::string dir, bool recursive = true);
	ENGINE_SHARED std::vector<std::string> filesInDirFullPath(std::string dir, std::string fileWildCard = "*.*");
	ENGINE_SHARED int filesInDirFullPath(std::string dir,std::string fileWildCard,std::vector<std::string> &files);
	ENGINE_SHARED std::string workingDirectory();
	ENGINE_SHARED std::vector<std::string> foldersInDir(std::string dir);
	ENGINE_SHARED bool validDir(std::string dir);
	ENGINE_SHARED std::string extractFileName(std::string fullPath);
	ENGINE_SHARED std::string extractExtension(std::string fullPath);
	ENGINE_SHARED std::string extractFilePath(std::string fullPath);

	ENGINE_SHARED FILETIME LastWritten(std::wstring filePath, bool& validFile);
	ENGINE_SHARED bool OutOfDate(std::string sourceFilePath, std::string generatedFilePath);
	ENGINE_SHARED bool OutOfDate(std::wstring sourceFilePath, std::wstring generatedFilePath);

	//returns new pos in file, sizeLeft will be edited as file is read
	ENGINE_SHARED fileByte * readLine(fileByte * currentPos, uint& sizeLeft, std::string& out);
	ENGINE_SHARED int lineCount(fileByte * file, uint size);

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