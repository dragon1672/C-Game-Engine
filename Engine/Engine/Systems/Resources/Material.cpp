#include "Material.h"
#include <Engine/IO/Stream.h>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/GameEvents.h>


#pragma region define helpers
#define MATERIAL_CONSTR_TEXTURE(name,properCase)\
	name = Object::NULL_OBJECT_ID(); \
	uniformIndex##properCase = -1; \
	has##properCase = false; \
	name##Offset.x = name##Offset.y = 0; \
	name##Scale.x  = name##Scale.y  = 1; \

#define MATERIAL_STRING(a) #a
#define MATERIAL_STRINGY(a,b) MATERIAL_STRING(a##b)

#define MATERIAL_ADD_UNIFORM(arrayName,indexName,name,properCase)\
	uniformIndex##properCase = indexName; \
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRING(name)            , ParameterType::PT_TEXTURE2D, properCase##()   );\
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRINGY(has,properCase) , ParameterType::PT_BOOLEAN,   &has##properCase );\
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRINGY(name,Scale)     , ParameterType::PT_VEC2,      &name##Scale[0]  );\
	arrayName##[##indexName##++] = ShaderUniformPram( MATERIAL_STRINGY(name,Offset)    , ParameterType::PT_VEC2,      &name##Offset[0] )

#define SAVE_TEXTURE_TO_STREAM(stream_name,name,Propercase)\
	stream_name << name << has##Propercase << name##Scale << name##Offset

#define LOAD_TEXTURE_FROM_STREAM(stream_name,name,Propercase)\
	stream_name >> name >> has##Propercase >> name##Scale >> name##Offset; \
	Propercase (name)/* updates uniforms*/

#pragma  endregion

ShaderUniformPram * Material::getUniforms()
{
	return &uniforms[0];
}
int Material::numOfUniforms()
{
	return sizeof(uniforms)/sizeof(*uniforms);
}
std::string Material::getShaderName()
{
	return "Material";
}

void Material::Save(Stream&s)
{
	SAVE_TEXTURE_TO_STREAM(s,diffuse,  Diffuse  );
	SAVE_TEXTURE_TO_STREAM(s,normalMap,NormalMap);
	SAVE_TEXTURE_TO_STREAM(s,ambOcc,   AmbOcc   );
	SAVE_TEXTURE_TO_STREAM(s,alphaMask,AlphaMask);
}



void Material::Load(Stream&s)
{
	LOAD_TEXTURE_FROM_STREAM(s,diffuse,  Diffuse  );
	LOAD_TEXTURE_FROM_STREAM(s,normalMap,NormalMap);
	LOAD_TEXTURE_FROM_STREAM(s,ambOcc,   AmbOcc   );
	LOAD_TEXTURE_FROM_STREAM(s,alphaMask,AlphaMask);
}

Material::Material()
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

void Material::start()
{
	Diffuse  (diffuse  );
	NormalMap(normalMap);
	AmbOcc   (ambOcc   );
	AlphaMask(alphaMask);
}

void Material::Clone(Material& ret)
{
	ret.Diffuse  (diffuse  );
	ret.NormalMap(normalMap);
	ret.AmbOcc   (ambOcc   );
	ret.AlphaMask(alphaMask);
}

Material::~Material()
{

}
