#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderObject.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Tools/GlmWrap.h>
#include <vector>
#include <Engine/Systems/ResourceManager.h>
#include <Engine/IO/StreamableObject.h>

#pragma region define helpers
#define MATERIAL_TEXTURE_GET_SET_WRAP(name,properCase) \
	inline TextureInfo * properCase##() const { return resourceManager.getTextureInfo(name); }      \
	inline void properCase##(TextureInfo * val) {                     \
		name = val != nullptr ? val->getID() : Object::NULL_OBJECT_ID();                                                   \
		has##properCase = name != Object::NULL_OBJECT_ID();                            \
		uniforms[##uniformIndex##properCase##].Pointer(val);         \
	}                                                                 \
	inline void properCase##(double index) {                          \
	name = index##;             \
		has##properCase = name != Object::NULL_OBJECT_ID();                            \
		uniforms[##uniformIndex##properCase##].Pointer( properCase##() );         \
	}                                                                 \
	inline glm::vec2& properCase##Scale()  { return name##Scale; }    \
	inline glm::vec2& properCase##Offset() { return name##Offset; }

#define MATERIAL_INIT_TEXTURE(name,properCase)\
	double name; bool has##properCase; glm::vec2 name##Scale, name##Offset; int uniformIndex##properCase;

#pragma  endregion

class ENGINE_SHARED Material : public ShaderObject, public StreamableObject {
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

	Material();
	wrap::vec4 color;

	virtual ShaderUniformPram * getUniforms();

	virtual int numOfUniforms();

	virtual std::string getShaderName();

	virtual void Save(Stream&s);

	virtual void Load(Stream&s);

};