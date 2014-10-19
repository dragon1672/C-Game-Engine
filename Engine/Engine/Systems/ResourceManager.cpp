#include "ResourceManager.h"

IMPLEMENT_SINGLETON(ResourceManager);

Mesh * ResourceManager::addMesh(const char * name)
{
	geos.push_back(Mesh(name));
	MeshObjs.Register(geos.last());
	return &geos.last();
}
Mesh * ResourceManager::addMesh(const char * name, Neumont::ShapeData& NUCrap)
{
	geos.push_back(Mesh(name));
	Mesh& ret = geos.last();
	for (int i = 0; i < NUCrap.numVerts; i++) {
		auto& v = NUCrap.verts[i];
		ret.verts.push_back(Vert(v.position,v.color,v.position,glm::vec4(),v.uv));
	}
	for (int i = 0; i < NUCrap.numIndices; i++) {
		ret.indices.push_back(NUCrap.indices[i]);
	}
	MeshObjs.Register(geos.last());
	return &geos.last();
}
Mesh * ResourceManager::addMesh(const char * name, std::string filePath)
{
	return addMesh(filePath.c_str());
}
Mesh * ResourceManager::addMesh(const char * name, const char * filePath)
{
	geos.push_back(FileIO::loadMeshFromFile(filePath),name);
	MeshObjs.Register(geos.last());
	return &geos.last();
}
ShaderProgram * ResourceManager::addShader_file(const char * name, const char * vertFilePath, const char * fragFilePath)
{
	return addShader_src(name, FileIO::readFile(vertFilePath),FileIO::readFile(fragFilePath));
}
ShaderProgram * ResourceManager::addShader_file(const char * name, std::string vertFilePath, std::string fragFilePath)
{
	return addShader_src(name, FileIO::readFile(vertFilePath),FileIO::readFile(fragFilePath));
}
ShaderProgram * ResourceManager::addShader_src (const char * name, std::string vert, std::string frag)
{
	return addShader_src(name, vert.c_str(),frag.c_str());
}
ShaderProgram * ResourceManager::addShader_src (const char * name, const char * vert, const char * frag)
{
	shaders.push_back(ShaderProgram(name));
	ShaderObjs.Register(geos.last());
	shaders.last().buildBasicProgram(vert,frag);
	return &shaders.last();
}
void ResourceManager::init()
{
	foreachOnAll([](Resource& data) { data.init(); });
}
void ResourceManager::PassDownToHardWare()
{
	foreachOnAll([](Resource& data) { data.PassDownToHardWare(); });
}
void ResourceManager::update()
{
	foreachOnAll([](Resource& data) { data.update(); });
}
