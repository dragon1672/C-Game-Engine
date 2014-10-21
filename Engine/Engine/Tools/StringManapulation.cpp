#include "StringManapulation.h"
#include <sstream>




std::vector<std::string>& StringManapulation::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string>  StringManapulation::split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::string StringManapulation::ToLower(std::string str)
{
	//converts std::string to lowercase
	for (unsigned int i=0; i<str.length(); i++) {
		str[i] = (char)tolower(str[i]);
	}
	return str;
}

std::string StringManapulation::ToUpper(std::string str)
{
	//converts string to lowercase
	for (unsigned int i=0; i<str.length(); i++) {
		str[i] = (char)toupper(str[i]);
	}
	return str;
}
