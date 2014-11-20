#include "StringManapulation.h"
#include <sstream>
#include <Engine/TypeDefs.h>
#include <Engine/Tools/CollectionEditing.h>


namespace StringManapulation {

	void split(const std::string &s, char delim, std::vector<std::string> &elems, bool ignoreBlank)
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			if(!ignoreBlank || item != "") {
				elems.push_back(item);
			}
		}
	}

	std::vector<std::string>  split(const std::string &s, char delim, bool ignoreBlank)
	{
		std::vector<std::string> elems;
		split(s, delim, elems,ignoreBlank);
		return elems;
	}

	std::string ToLower(std::string str)
	{
		//converts std::string to lowercase
		for (unsigned int i=0; i<str.length(); i++) {
			str[i] = (char)tolower(str[i]);
		}
		return str;
	}

	std::string ToUpper(std::string str)
	{
		//converts string to lowercase
		for (unsigned int i=0; i<str.length(); i++) {
			str[i] = (char)toupper(str[i]);
		}
		return str;
	}

	std::string trimStart(std::string src,char toTrim)
	{
		uint offset = 0;
		for (; offset < src.length() && src[offset] == toTrim; offset++);
		return src.substr(offset);
	}

	std::string trimStart(std::string src, char * list, int count)
	{
		std::string ret = src;
		for (int i = 0; i < count; i++)
			ret = trimStart(ret,list[i]);
		return ret;
	}

	ENGINE_SHARED std::string trimStart(std::string src, std::unordered_set<char> list)
	{
		uint offset = 0;
		for (; offset < src.length() && Collections::contains(list,src[offset]); offset++);
		return src.substr(offset);
	}

	std::string trimEnd(std::string src,char toTrim)
	{
		int offset = src.length()-1;
		for (; offset >= 0 && src[offset] == toTrim; offset--);
		return src.substr(0,offset+1);
	}

	std::string trimEnd(std::string src, char * list, int count)
	{
		std::string ret = src;
		for (int i = 0; i < count; i++)
			ret = trimStart(ret,list[i]);
		return ret;
	}

	ENGINE_SHARED std::string trimEnd(std::string src, std::unordered_set<char> list)
	{
		int offset = src.length()-1;
		for (; offset >= 0 && Collections::contains(list,src[offset]); offset--);
		return src.substr(0,offset+1);
	}

	std::string trim(std::string src,char toTrim)
	{
		return trimEnd(trimStart(src,toTrim),toTrim);
	}

	std::string trim(std::string src, char * list, int count)
	{
		std::string ret = src;
		for (int i = 0; i < count; i++)
			ret = trim(ret,list[i]);
		return ret;
	}

	ENGINE_SHARED std::string trim(std::string src, std::unordered_set<char> list)
	{
		return trimEnd(trimStart(src,list),list);
	}

	std::string trimWhiteSpace(std::string src)
	{
		std::unordered_set<char> list;
		list.emplace(' ');
		list.emplace('\n');
		list.emplace('\t');
		return trim(src,list);
	}

	std::string trimWhiteSpaceStart(std::string src)
	{
		std::unordered_set<char> list;
		list.emplace(' ');
		list.emplace('\n');
		list.emplace('\t');
		return trimStart(src,list);
	}

	std::string repeat(int total, std::string strA)
	{
		std::string str;
		for (int a=0; a<total; a++) {
			str += strA;
		}
		return str;
	}

	std::string reverse(std::string str)
	{
		std::string newstr = "";
		for (int a=str.length()-1; a>=0; a--) {
			newstr+=str[a];
		}
		return newstr;
	}

	std::string center(std::string text, int length, char filler)
	{
		std::string str;
		for (unsigned int i=0; i<(length-text.length()-((length/2)-(text.length()/2))); i++) {str += filler;}
		str += text;
		for (unsigned int i=0; i<(length/2)-(text.length()/2); i++) {str += filler;}
		return str;
	}

	std::string center(std::string back, std::string toCenter)
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

	std::string replace(char what,char with,std::string source)
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

	std::string replace(std::string what,std::string with,std::string source)
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

	bool startsWith(const char * source,std::string toCheck)
	{
		return startsWith(std::string(source),toCheck);
	}
	bool startsWith(std::string source, std::string toCheck)
	{
		return match(source,toCheck,0);
	}

	std::string LoadingBar(float percent,uint length, bool showPercent)
	{
		char bar=(uchar)178;//mostly dark
		//bar=(uchar)176;//lightest
		//bar=(uchar)177;//med
		std::string str;
		str+=(uchar)221;
		for (float i=0; i<length; i++) {
			if (i/length < percent) {
				str+=bar;
			} else {
				str+=' ';
			}
		}
		std::string num = toString(floor(percent*100));
		if (showPercent && length>num.length()+3) {
			str=center(str,"-"+num+"%-");
		}
		str+=(uchar)222;
		return str;
	}

	//private
	template<typename T>
	std::string sstreamToString(T data) {
		std::stringstream ss;
		ss << data;
		return ss.str();
	}

	template<>
	std::string toString(int num)
	{
		return sstreamToString(num);
	}

	template<>
	std::string toString(long num)
	{
		return sstreamToString(num);
	}

	template<>
	std::string toString(short num)
	{
		return sstreamToString(num);
	}

	template<>
	std::string toString(float num)
	{
		return sstreamToString(num);
	}

	template<>
	std::string toString(double num)
	{
		return sstreamToString(num);
	}

	template<>
	std::string toString(unsigned int num)
	{
		return sstreamToString(num);
	}

	template<>
	std::string toString(unsigned long num)
	{
		return sstreamToString(num);
	}

	template<>
	std::string toString(unsigned short num)
	{
		return sstreamToString(num);
	}
}