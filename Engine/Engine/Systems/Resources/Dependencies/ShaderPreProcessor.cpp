#include "ShaderPreProcessor.h"
#include <sstream>
#include <map>
#include <vector>
#include <Engine/Tools/StringManapulation.h>

namespace {
	std::map<std::string,std::string> initReplacements() {
		// all keys should be lowercase
		std::map<std::string,std::string> ret;
		//default ids
		ret["define"]   = "#define";
		ret["undef"]    = "#undef";
		ret["if"]       = "#if";
		ret["ifdef"]    = "#ifdef";
		ret["ifndef"]   = "#ifndef";
		ret["else"]     = "#else";
		ret["elif"]     = "#elif";
		ret["endif"]    = "#endif";
		ret["error"]    = "#error";
		ret["pragma"]   = "#pragma";
		ret["xtension"] = "#xtension";
		ret["version"]  = "#version";
		ret["line"]     = "#line";
		//end of defaults
		ret["shaderStart"]   = "";
		ret["shaderStart"]   = "";
		ret["main_export"]   = "";
		ret["main_setglPos"] = "";



		return ret;
	}
	std::map<std::string,std::string> replacements = initReplacements();

	std::string replaceLine(std::string line) {
		std::string code = StringManapulation::ToLower(StringManapulation::split(line,' ')[0]);
		return replacements.find(code) == replacements.end() ? line : replacements[code];
	}
}




std::string ENGINE_SHARED ShaderPreProcessor::processGLSL(std::string src)
{
	std::string s("Somewhere down the road");
	std::istringstream iss(s);
	std::string ret;
	do
	{
		std::string sub;
		iss >> sub;
		//work with sub
		if(sub[0] == '#') {

		} else {
			ret += sub;
		}
	} while (iss);
	return ret;
}
