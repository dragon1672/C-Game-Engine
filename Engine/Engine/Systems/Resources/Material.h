#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderObject.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Tools/GlmWrap.h>
#include <vector>

#define MATERIAL_TEXTURE_GET_SET_WRAP(name,properCase) \
	TextureInfo * properCase##() const { return name##; }\
	void properCase##(TextureInfo * val) { name = val; has##properCase = name != nullptr; }
#define MATERIAL_INIT_TEXTURE(name,properCase)\
	TextureInfo * name; bool has##properCase;
#define MATERIAL_CONSTR_TEXTURE(name,properCase)\
	name = nullptr; \
	has##properCase = false;

class ENGINE_SHARED Material : public ShaderObject {
	ShaderUniformPram uniforms[8];
	MATERIAL_INIT_TEXTURE(diffuse,  Diffuse  );
	MATERIAL_INIT_TEXTURE(normalMap,NormalMap);
	MATERIAL_INIT_TEXTURE(ambOcc,   AmbOcc   );
	MATERIAL_INIT_TEXTURE(alphaMask,AlphaMask);
public:
	MATERIAL_TEXTURE_GET_SET_WRAP(diffuse,  Diffuse  );
	MATERIAL_TEXTURE_GET_SET_WRAP(normalMap,NormalMap);
	MATERIAL_TEXTURE_GET_SET_WRAP(ambOcc,   AmbOcc   );
	MATERIAL_TEXTURE_GET_SET_WRAP(alphaMask,AlphaMask);

	Material()
		:
		diffuse(nullptr), normalMap(nullptr), ambOcc(nullptr), alphaMask(nullptr)
	{
		MATERIAL_CONSTR_TEXTURE(diffuse,  Diffuse  );
		MATERIAL_CONSTR_TEXTURE(normalMap,NormalMap);
		MATERIAL_CONSTR_TEXTURE(ambOcc,   AmbOcc   );
		MATERIAL_CONSTR_TEXTURE(alphaMask,AlphaMask);

		uniforms[0] = ShaderUniformPram("diffuse",   ParameterType::PT_TEXTURE2D,  diffuse      );
		uniforms[1] = ShaderUniformPram("normalMap", ParameterType::PT_TEXTURE2D,  normalMap    );
		uniforms[2] = ShaderUniformPram("ambOcc",    ParameterType::PT_TEXTURE2D,  ambOcc       );
		uniforms[3] = ShaderUniformPram("alphaMask", ParameterType::PT_TEXTURE2D,  alphaMask    );
		uniforms[4] = ShaderUniformPram("hasDiffuse",ParameterType::PT_BOOLEAN,   &hasDiffuse   );
		uniforms[5] = ShaderUniformPram("hasNormal", ParameterType::PT_BOOLEAN,   &hasNormalMap );
		uniforms[6] = ShaderUniformPram("hasAmbOcc", ParameterType::PT_BOOLEAN,   &hasAmbOcc    );
		uniforms[7] = ShaderUniformPram("hasAlpha",  ParameterType::PT_BOOLEAN,   &hasAlphaMask );
	}
	wrap::vec4 color;

	virtual ShaderUniformPram * getUniforms();

	virtual int numOfUniforms();

	virtual std::string getShaderName();

};