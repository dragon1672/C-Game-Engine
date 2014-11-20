#pragma once

#include <string>
#include <ExportHeader.h>

namespace EngineParser {
	//output will not be modified if invalid string
	ENGINE_SHARED bool tryParseDouble(std::string& src, double& out);
	ENGINE_SHARED bool tryParseFloat(std::string& src, float& out);
	ENGINE_SHARED bool tryParseInt(std::string& src, int& out);


	//assumes starting on number, will "gobble" string until invalid number found
	//returns false if no number found
	//when it returns false it will still gobble the first character of the string
	//gobble will also take out the following character
	//example: "1 23 456" -> "23 456" // note the "1 " was taken out of the string
	ENGINE_SHARED bool tryParseDoubleGobbleSrc(std::string& src, double& out);
	ENGINE_SHARED bool tryParseFloatGobbleSrc(std::string& src, float& out);
	ENGINE_SHARED bool tryParseIntGobbleSrc(std::string& src, int& out);
}