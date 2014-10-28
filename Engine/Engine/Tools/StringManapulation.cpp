#include "StringManapulation.h"
#include <sstream>
#include <Engine/TypeDefs.h>




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
	uint offset = 0;
	for (; offset < src.length() && src[offset] == toTrim; offset++);
	return src.substr(offset);
}

std::string StringManapulation::trimStart(std::string src, char * list, int count)
{
	std::string ret = src;
	for (int i = 0; i < count; i++)
		ret = trimStart(ret,list[i]);
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

std::string StringManapulation::repeat(int total, std::string strA)
{
	std::string str;
	for (int a=0; a<total; a++) {
		str += strA;
	}
	return str;
}

std::string StringManapulation::reverse(std::string str)
{
	std::string newstr = "";
	for (int a=str.length()-1; a>=0; a--) {
		newstr+=str[a];
	}
	return newstr;
}

std::string StringManapulation::center(std::string text, int length, char filler)
{
	std::string str;
	for (unsigned int i=0; i<(length-text.length()-((length/2)-(text.length()/2))); i++) {str += filler;}
	str += text;
	for (unsigned int i=0; i<(length/2)-(text.length()/2); i++) {str += filler;}
	return str;
}

std::string StringManapulation::center(std::string back, std::string toCenter)
{
	if (back.length() < toCenter.length()) {
		return "invalid data given";
	}
	std::string str;
	for (unsigned int i=0; i<(back.length()-toCenter.length()-((back.length()/2)-(toCenter.length()/2))); i++) {
		str += back[i];
	}
	str += toCenter;
	for (unsigned int i=0; i<(back.length()/2)-(toCenter.length()/2); i++) {
		str += back[str.length()];
	}
	return str;
}

std::string StringManapulation::replace(char what,char with,std::string source)
{
	for (unsigned int i=0;i<source.length();i++) {
		if(source[i]==what) {
			source[i]=with;
		}
	}
	return source;
}

namespace {
	bool match(std::string& master, std::string& toMatchWith, int indexIntoA) {
		if(master.length()-indexIntoA < toMatchWith.length()) {
			return false;
		}
		for (uint i = 0; i < toMatchWith.length(); i++) {
			if(master[indexIntoA + i] != toMatchWith[i])
				return false;
		}
		return true;
	}
}

std::string StringManapulation::replace(std::string what,std::string with,std::string source)
{
	std::string ret;
	for (uint i = 0; i < source.length(); i++) {
		if(match(source,what,i)) {
			ret += with;
			i += what.length()-1;
		} else {
			ret += source[i];
		}
	}
	return ret;
}

bool StringManapulation::startsWith(const char * source,std::string toCheck)
{
	if(source == nullptr || strlen(source) < toCheck.length()) return false;
	for (uint i = 0; i < toCheck.length(); i++) {
		if(source[i] != toCheck[i]) return false;
	}
	return true;
}
bool StringManapulation::startsWith(std::string source, std::string toCheck)
{
	return startsWith(source.c_str(),toCheck);
}
