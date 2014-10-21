#include "ShaderPreProcessor.h"
#include <sstream>
#include <map>
#include <vector>
#include <Engine/Tools/StringManapulation.h>
#include <Engine/TypeDefs.h>

namespace {
	std::map<std::string,std::string> initReplacements() {
		// all keys should be lowercase
		std::map<std::string,std::string> ret;
		ret["#vert_shaderstart"]   = "[layouts, outs for each of the layouts to the frag, default matrix]";
		ret["#vert_main_export"]   = "[assign outs from layouts]";
		ret["#vert_main_setglPos"] = "[set gl_pos using matrix]";


		return ret;
	}
	std::map<std::string,std::string>   replacements = initReplacements();
	std::map<ParameterType,std::string> initPrams() {
		std::map<ParameterType,std::string> ret;
		ret[ParameterType::PT_BOOLEAN]    =  "bool" ;
		ret[ParameterType::PT_FLOAT]      =  "float";
		ret[ParameterType::PT_INT]        =  "int"  ;
		ret[ParameterType::PT_MAT3]       =  "mat3" ;
		ret[ParameterType::PT_MAT4]       =  "mat4" ;
		ret[ParameterType::PT_TEXTURE]    =  "sampler2D"  ;
		ret[ParameterType::PT_TEXTURE2D]  =  "sampler2D"  ;
		ret[ParameterType::PT_TEXTURE3D]  =  "samplerCube";
		ret[ParameterType::PT_VEC2]       =  "vec2";
		ret[ParameterType::PT_VEC3]       =  "vec3";
		ret[ParameterType::PT_VEC4]       =  "vec4";

		return ret;
	}
	std::map<ParameterType,std::string> typeToGLSL   = initPrams();

	std::string replaceLine(std::string line) {
		std::string code = StringManapulation::ToLower(StringManapulation::split(line,' ')[0]);
		return replacements.find(code) == replacements.end() ? line : replacements[code];
	}
}




std::string ShaderPreProcessor::processGLSL(std::string src)
{
	auto lines = StringManapulation::split(src,'\n');
	std::string ret = "";
	for (uint i = 0; i < lines.size(); i++) {
		ret += replaceLine(lines[i]);
		if(i!=lines.size()-1) // not last line
			ret += "\n";
	}
	return ret;
}

void ShaderPreProcessor::registerShaderObject(ShaderObject& obj) {
	registerShaderObject(&obj);
}
void ShaderPreProcessor::registerShaderObject(ShaderObject * obj)
{
	std::string index = "#component_"+StringManapulation::ToLower(obj->getName());
	if(replacements.find(index) == replacements.end()) return; // already entered
	std::string uniformInclude = "";
	for (int i = 0; i < obj->numOfUniforms(); i++)
	{
		ShaderUniformPram& pram = obj->getUniforms()[i];
		uniformInclude += "uniform "+typeToGLSL[pram.Type()]+" "+pram.Title() + ";\n";
	}
	replacements[index] = uniformInclude;
}
