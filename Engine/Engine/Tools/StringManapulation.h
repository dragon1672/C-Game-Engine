#pragma once

#include <ExportHeader.h>
#include <string>
#include <vector>

namespace StringManapulation {
	ENGINE_SHARED std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
	ENGINE_SHARED std::vector<std::string>  split(const std::string &s, char delim);
	ENGINE_SHARED std::string ToLower(std::string str);
	ENGINE_SHARED std::string ToUpper(std::string str);
}