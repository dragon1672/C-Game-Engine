#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <Engine/Tools/ConstVector.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Systems/Resources/Mesh.h>
#include <Engine/Systems/Resources/ShaderProgram.h>

#define resourceManager

class ResourceManager {
	DEFINE_SINGLETON(ResourceManager);
private:
	ConstVector<ShaderProgram> shaders;
	ConstVector<Mesh> geo;
	ConstVector<TextureInfo> textures;
	//ConstVector<

public:
	
};