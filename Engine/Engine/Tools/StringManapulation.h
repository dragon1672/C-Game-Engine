#pragma once

#include <ExportHeader.h>
#include <string>
#include <vector>

namespace StringManapulation {
	ENGINE_SHARED std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
	ENGINE_SHARED std::vector<std::string>  split(const std::string &s, char delim);
	ENGINE_SHARED std::string ToLower(std::string str);
	ENGINE_SHARED std::string ToUpper(std::string str);
	ENGINE_SHARED std::string trimStart(std::string src,char toTrim);
	ENGINE_SHARED std::string trimEnd(std::string src,char toTrim);
	ENGINE_SHARED std::string trim(std::string src,char toTrim);
	ENGINE_SHARED std::string trim(std::string src, char * list, int count);
	ENGINE_SHARED std::string trimStart(std::string src, char * list, int count);
	ENGINE_SHARED std::string trimEnd(std::string src, char * list, int count);
	ENGINE_SHARED std::string trimWhiteSpace(std::string src);
	ENGINE_SHARED std::string trimWhiteSpaceStart(std::string src);
}