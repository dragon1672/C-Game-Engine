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
		ret["#vert_shaderstart"]   = ""
			//"[layouts, outs for each of the layouts to the frag, default matrix]"
			"#version 400                                                              \n"
			"in layout(location=0) vec3 pos;                                           \n"
			"in layout(location=1) vec4 col;                                           \n"
			"in layout(location=2) vec3 norm;                                          \n"
			"in layout(location=3) vec4 tangent                                        \n"
			"in layout(location=4) vec2 uv;                                            \n"
			"                                                                          \n"
			"out vec3 fragModelPos; // pos with no transform                           \n"
			"out vec3 fragWorldPos; // pos with model to world transform               \n"
			"out vec3 fragCameraPos; // pos with model to world and camera transform   \n"
			"out vec3 fragScreenPos; // pos fully transformed (used as gl_pos)         \n"
			"out vec4 fragCol;                                                         \n"
			"out vec3 fragNorm;                                                        \n"
			"out vec4 fragTan;                                                         \n"
			"out vec2 fragUv;                                                          \n"
			"                                                                          \n"
			"uniform mat4x4 model2WorldTransform;                                      \n"
			"uniform mat4x4 world2Cam;                                                 \n"
			"uniform mat4x4 model2Cam; // world2Cam * model2WorldTransform             \n"
			"uniform mat4x4 viewTransform; // projection matrix                        \n"
			"uniform mat4x4 MVP;                                                       \n"
			"";
		ret["#vert_main_export"]   = ""
			//"[assign outs from layouts]"
			"   fragModelPos  = pos;                                \n"
			"   fragModelPos  = model2WorldTransform * vec4(pos,1); \n"
			"   fragWorldPos  = world2Cam * vec4(pos,1);            \n"
			"   fragCameraPos = model2Cam * vec4(pos,1);            \n"
			"   fragScreenPos = MVP * vec4(pos,1);                  \n"
			"   fragCol = col;                                      \n"
			"   fragNorm = norm;                                    \n"
			"   fragTan = tangent;                                  \n"
			"   fragUv = uv;                                        \n"
			"";
		ret["#vert_main_setglpos"] = ""
			//"[set gl_pos using matrix]"
			"gl_Position = fragWorldPos;";
			"";
		ret["#frag_main_import"]   = ""
			//"[get outs from layouts]"
			"int vec3 fragModelPos;  \n"
			"int vec3 fragModelPos;  \n"
			"int vec3 fragWorldPos;  \n"
			"int vec3 fragCameraPos; \n"
			"int vec3 fragScreenPos; \n"
			"int vec3 fragCol;       \n"
			"int vec3 fragNorm;      \n"
			"int vec3 fragTan;       \n"
			"int vec3 fragUv;        \n"
			"";


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
		std::string code = StringManapulation::trimWhiteSpaceStart(StringManapulation::ToLower(StringManapulation::split(line,' ')[0]));
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
