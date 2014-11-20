#include "Parsing.h"




bool EngineParser::tryParseDouble(std::string& src, double& out)
{
	if(src.size() ==0 ) return false;
	double ret = 0;
	double power = 1;
	bool afterDot = false;

	bool negitive = src[0] == '-';

	unsigned int i = negitive ? 1 : 0;
	for (; i < src.size(); i++) {
		if('0' <= src[i] && src[i] <= '9') {
			if(!afterDot) {
				ret *= 10; // move numbers to the left as new numbers are found
				ret += src[i] - '0';
			} else {
				power /= 10.0;
				double tmp = (src[i] - '0');
				ret += tmp * power;
			}
		} else {
			if(!afterDot && src[i] == '.') {
				afterDot = true;
			} else {
				return false;
			}
		}
	}
	out = ret * (negitive ? -1 : 1);
	return true;
}

bool EngineParser::tryParseFloat(std::string& src, float& out)
{
	double tmp;
	bool ret = tryParseDouble(src,tmp);
	out = (float)tmp;
	return ret;
}

bool EngineParser::tryParseInt(std::string& src, int& out)
{
	if(src.size() == 0) return false;
	int ret = 0;
	bool negitive = src[0]=='-';

	unsigned int i = negitive ? 1 : 0;
	for (; i < src.size(); i++) {
		if('0' <= src[i] && src[i] <= '9') {
			ret *= 10;
			ret += src[i] - '0';
		} else {
			return false; // break out now
		}
	}
	out = ret * (negitive ? -1 : 1);
	return true;
}

bool EngineParser::tryParseDoubleGobbleSrc(std::string& src, double& out)
{
	if(src.size() ==0 ) return false;
	double ret = 0;
	double power = 1;
	bool afterDot = false;
	bool done = false;
	bool valid = false;

	bool negitive = src[0] == '-';

	unsigned int i = negitive ? 1 : 0;
	for (; !done && i < src.size(); i++) {
		if('0' <= src[i] && src[i] <= '9') {
			valid = true;
			if(!afterDot) {
				ret *= 10; // move numbers to the left as new numbers are found
				ret += src[i] - '0';
			} else {
				power /= 10.0;
				double tmp = (src[i] - '0');
				ret += tmp * power;
			}
		} else {
			if(!afterDot && src[i] == '.') {
				afterDot = true;
			} else {
				done = true;
			}
		}
	}
	src = src.substr(i); // gobble gobble
	if(valid) {
		out = ret * (negitive ? -1 : 1);
	}
	return valid;
}

bool EngineParser::tryParseFloatGobbleSrc(std::string& src, float& out)
{
	double tmp;
	bool ret = tryParseDoubleGobbleSrc(src,tmp);
	out = (float)tmp;
	return ret;
}

bool EngineParser::tryParseIntGobbleSrc(std::string& src, int& out)
{
	if(src.size() == 0) return false;
	int ret = 0;
	bool done = false;
	bool valid = true;

	bool negitive = false;
	bool startedParsing = false; // this will skip large chunks of dlim

	unsigned int i;
	for (i = 0; !done && i < src.size(); i++) {
		if('0' <= src[i] && src[i] <= '9') {
			startedParsing = true;
			ret *= 10;
			ret += src[i] - '0';
		} else {
			if(i==0 && src[i] == '-') {
				negitive = true;
			} else {
				done = true;
			}
		}
	}
	src = src.substr(i); // gobble
	valid = valid && startedParsing;
	if(valid) {
		out = ret * (negitive ? -1 : 1);
	}
	return valid;
}
