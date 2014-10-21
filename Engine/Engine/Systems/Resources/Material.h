#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderObject.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Tools/GlmWrap.h>
#include <vector>

class ENGINE_SHARED Material : public ShaderObject {
	std::vector<ShaderUniformPram> uniforms;
public:
	Material() {
		uniforms.push_back(ShaderUniformPram("diffuse",   ParameterType::PT_TEXTURE2D,  diffuse   ));
		uniforms.push_back(ShaderUniformPram("normalMap", ParameterType::PT_TEXTURE2D,  normalMap ));
		uniforms.push_back(ShaderUniformPram("ambOcc",    ParameterType::PT_TEXTURE2D,  ambOcc    ));
		uniforms.push_back(ShaderUniformPram("alphaMask", ParameterType::PT_TEXTURE2D,  alphaMask ));
		uniforms.push_back(ShaderUniformPram("hasDiffuse",ParameterType::PT_BOOLEAN,   &hasDiffuse));
		uniforms.push_back(ShaderUniformPram("hasNormal", ParameterType::PT_BOOLEAN,   &hasNormal ));
		uniforms.push_back(ShaderUniformPram("hasAmbOcc", ParameterType::PT_BOOLEAN,   &hasAmbOcc ));
		uniforms.push_back(ShaderUniformPram("hasAlpha",  ParameterType::PT_BOOLEAN,   &hasAlpha  ));
	}
	wrap::vec4 color;
	TextureInfo * diffuse,  * normalMap, * ambOcc,  * alphaMask;
	bool          hasDiffuse, hasNormal,   hasAmbOcc, hasAlpha;

	virtual ShaderUniformPram * getUniforms();

	virtual int numOfUniforms();

	virtual std::string getName();

};