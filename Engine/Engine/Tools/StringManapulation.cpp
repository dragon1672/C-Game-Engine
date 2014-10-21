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

std::string StringManapulation::trimStart(std::string src,char toTrim)
{
	int offset = 0;
	for (; offset < src.length() && src[offset] == toTrim; offset++);
	return src.substr(offset);
}

std::string StringManapulation::trimStart(std::string src, char * list, int count)
{
	std::string ret = src;
	for (int i = 0; i < count; i++)
		ret = trimEnd(ret,list[i]);
	return ret;
}

std::string StringManapulation::trimEnd(std::string src,char toTrim)
{
	int offset = src.length()-1;
	for (; offset >= 0 && src[offset] == toTrim; offset--);
	return src.substr(0,offset+1);
}

std::string StringManapulation::trimEnd(std::string src, char * list, int count)
{
	std::string ret = src;
	for (int i = 0; i < count; i++)
		ret = trimStart(ret,list[i]);
	return ret;
}

std::string StringManapulation::trim(std::string src,char toTrim)
{
	return trimEnd(trimStart(src,toTrim),toTrim);
}

std::string StringManapulation::trim(std::string src, char * list, int count)
{
	std::string ret = src;
	for (int i = 0; i < count; i++)
		ret = trim(ret,list[i]);
	return ret;
}

std::string StringManapulation::trimWhiteSpace(std::string src)
{
	char list[] = {' ','\n','\t'};
	return trim(src,list,sizeof(list)/sizeof(*list));
}

std::string StringManapulation::trimWhiteSpaceStart(std::string src)
{
	char list[] = {' ','\n','\t'};
	return trimStart(src,list,sizeof(list)/sizeof(*list));
}
