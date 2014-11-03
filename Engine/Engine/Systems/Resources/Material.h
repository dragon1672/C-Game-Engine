#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderObject.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Tools/GlmWrap.h>
#include <vector>
#include <Engine/Systems/ResourceManager.h>

#define MATERIAL_TEXTURE_GET_SET_WRAP(name,properCase) \
	inline TextureInfo * properCase##() const { return name##; }      \
	inline void properCase##(TextureInfo * val) {                     \
		name = val;                                                   \
		has##properCase = name != nullptr;                            \
		uniforms[##uniformIndex##properCase##].Pointer(name);         \
	}                                                                 \
	inline void properCase##(int index) {                             \
		name = resourceManager.getTextureInfo(##index##);             \
		has##properCase = name != nullptr;                            \
		uniforms[##uniformIndex##properCase##].Pointer(name);         \
	}                                                                 \
	inline glm::vec2& properCase##Scale()  { return name##Scale; }    \
	inline glm::vec2& properCase##Offset() { return name##Offset; }



#define MATERIAL_INIT_TEXTURE(name,properCase)\
	TextureInfo * name; bool has##properCase; glm::vec2 name##Scale, name##Offset; int uniformIndex##properCase;
#define MATERIAL_CONSTR_TEXTURE(name,properCase)\
	name = nullptr; \
	uniformIndex##properCase = -1; \
	has##properCase = false; \
	name##Offset.x = name##Offset.y = 0; \
	name##Scale.x  = name##Scale.y  = 1; \

#define MATERIAL_STRING(a) #a
#define MATERIAL_STRINGY(a,b) MATERIAL_STRING(a##b)

#define MATERIAL_ADD_UNIFORM(arrayName,indexName,name,properCase)\
	uniformIndex##properCase = indexName; \
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRING(name)            , ParameterType::PT_TEXTURE2D, name             );\
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRINGY(has,properCase) , ParameterType::PT_BOOLEAN,   &has##properCase );\
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRINGY(name,Scale)     , ParameterType::PT_VEC2,      &name##Scale[0]  );\
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRINGY(name,Offset)    , ParameterType::PT_VEC2,      &name##Offset[0] )

class ENGINE_SHARED Material : public ShaderObject {
	ShaderUniformPram uniforms[16];
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

		int index = 0;
		MATERIAL_ADD_UNIFORM(uniforms,index,diffuse,  Diffuse  );
		MATERIAL_ADD_UNIFORM(uniforms,index,normalMap,NormalMap);
		MATERIAL_ADD_UNIFORM(uniforms,index,ambOcc,   AmbOcc   );
		MATERIAL_ADD_UNIFORM(uniforms,index,alphaMask,AlphaMask);
	}
	wrap::vec4 color;

	virtual ShaderUniformPram * getUniforms();

	virtual int numOfUniforms();

	virtual std::string getShaderName();

};