#include "ShaderPreProcessor.h"
#include <sstream>
#include <map>
#include <vector>
#include <Engine/Tools/StringManapulation.h>

namespace {
	std::map<std::string,std::string> initReplacements() {
		// all keys should be lowercase
		std::map<std::string,std::string> ret;
		ret["#vert_shaderstart"]   = "[layouts, outs for each of the layouts to the frag, default matrix]";
		ret["#vert_main_export"]   = "[assign outs from layouts]";
		ret["#vert_main_setglPos"] = "[set gl_pos using matrix]";


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
	auto lines = StringManapulation::split(src,'\n');
	std::string ret = "";
	for (uint i = 0; i < lines.size(); i++) {
		if(lines[i][0] == '#') {
			ret += replaceLine(lines[i]);
		} else {
			ret += lines[i];
		}
		if(i!=lines.size()-1)
			ret += "\n";
	}
	return ret;
}
