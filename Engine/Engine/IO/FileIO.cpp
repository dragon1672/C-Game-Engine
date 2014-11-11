#include "FileIO.h"
#include <fstream>
#include <cassert>
#include <Engine/Tools/Printer.h>
#include <dirent.h>
#include <QtCore/QStringList>

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

	std::vector<std::string> filesInDirFullPath(std::string dir, std::string fileWildCard)
	{
		std::vector<std::string> ret;
		filesInDirFullPath(dir,fileWildCard,ret);
		return ret;
	}

	int filesInDirFullPath(std::string dir,std::string fileWildCard, std::vector<std::string> &files)
	{
		int returnValue = 0;

		if(dir.back() != '\\' || dir.back() != '/') dir += '\\';

		std::string pCmd = "dir /B /S " + std::string(dir) + fileWildCard;
		FILE* pipe = _popen(pCmd.c_str(), "rt");

		if( NULL == pipe) {
			printErr(100) "Getting file from",dir,"failed";
			returnValue = 1;
		} else {
			char buf[256];
			while (!feof(pipe)) {
				char* currentFile = fgets(buf,256,pipe);
				if(currentFile != NULL) {
					std::string file = std::string(buf);
					int length = file.length() - 1;
					file = file.substr(0, length);
					files.push_back(file);
				} else {
					printErr(100) "Invalid Directory: ",dir;
				}
			}
		}

		_pclose(pipe);
		return returnValue;
	}

	std::string workingDirectory()
	{
		std::string pCmd = "echo %cd%";
		FILE* pipe = _popen(pCmd.c_str(), "rt");

		std::string ret = "";

		if( NULL == pipe) {
			printErr(100) pCmd,"Command failed";
		} else {
			char buf[256];
			char* currentFile = fgets(buf,256,pipe);
			if(currentFile != NULL) {
				std::string file = std::string(buf);
				int length = file.length() - 1;
				file = file.substr(0, length);
				ret = file;
			} else {
				printErr(100) pCmd,"Command failed when getting line";
			}
		}

		_pclose(pipe);
		return ret;
	}

	std::string extractFilePath(std::string fullPath)
	{
		QString file(fullPath.c_str());
		QStringList pathChunks = file.split('/');
		if(pathChunks.size() == 1) pathChunks = file.split('\\');
		pathChunks.pop_back();
		std::string justPath;
		for(int i=0;i<pathChunks.size();i++)
			justPath += pathChunks[i].toStdString()+"\\";
		return justPath;
	}

	std::string extractExtension(std::string fullPath)
	{
		QString file(fullPath.c_str());
		QStringList tmp = file.split('.');
		QString extension = tmp[tmp.size()-1];
		return extension.toStdString();
	}

	std::string extractFileName(std::string fullPath)
	{
		std::string path = extractFilePath(fullPath);
		std::string ext = extractExtension(fullPath);
		return fullPath.substr(path.size(),fullPath.size()-path.size()-ext.size()-1); // minus 1 for the dot
	}

}