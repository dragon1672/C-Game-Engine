#pragma once

#include <Engine\Tools\Random\MyRandom.h>
#include <ExportHeader.h>
#include <string>

namespace Random {
	namespace rString {
		std::string ENGINE_SHARED makeString(int len, int rangeStart,int rangeEnd);
		std::string ENGINE_SHARED makeString(int len, char * options, int numOptions);
		std::string ENGINE_SHARED UppercaseLetters(int len);
		std::string ENGINE_SHARED LowercaseLetters(int len);
		std::string ENGINE_SHARED Letters(int len);
	}
}