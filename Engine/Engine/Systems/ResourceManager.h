#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <Engine/Tools/ConstVector.h>
#include <Engine/Renderer/TextureInfo.h>
#include <Engine/Renderer/Geo/Mesh.h>
#include <Engine/Renderer/Shader/ShaderProgram.h>

#define resourceManager

class ResourceManager {
	DEFINE_SINGLETON(ResourceManager);
private:
	ConstVector<ShaderProgram> shaders;
	ConstVector<Mesh> geo;
	ConstVector<TextureInfo> textures;

public:
	
};