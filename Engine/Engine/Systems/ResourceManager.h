#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <Engine/Tools/ConstVector.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Systems/Resources/Mesh.h>
#include <Engine/Systems/Resources/ShaderProgram.h>
#include <Engine/Systems/ObjectManager.h>
#include <ShapeData.h>
#include <functional>
#include <Engine/IO/FileIO.h>
#include <Engine/IO/MeshLoader.h>

#define resourceManager

class ResourceManager : public Resource {
	DEFINE_SINGLETON(ResourceManager);
private:
	ConstVector<ShaderProgram> shaders;
	ObjectManager ShaderObjs;
	ConstVector<Mesh> geos;
	ObjectManager MeshObjs;
	ConstVector<TextureInfo> textures;
	ObjectManager TextureObjs;
	void foreachOnAll(std::function<void(Resource&)> func) {
		for (int i = 0; i < shaders.size();  i++) func(shaders[i]);
		for (int i = 0; i < geos.size();     i++) func(geos[i]);
		for (int i = 0; i < textures.size(); i++) func(textures[i]);
	}
public:

	Mesh * addMesh();
	Mesh * addMesh(Neumont::ShapeData& NUCrap);
	Mesh * addMesh(Mesh * toCopy);
	Mesh * addMesh(std::string filePath);
	Mesh * addMesh(const char * filePath);

	ShaderProgram * addShader_file(const char * vertFilePath, const char * fragFilePath);
	ShaderProgram * addShader_file(std::string vertFilePath, std::string fragFilePath);
	ShaderProgram * addShader_src(std::string vert, std::string frag);
	ShaderProgram * addShader_src(const char * vert, const char * frag);


	void init();

	void PassDownToHardWare();

	void update();
};