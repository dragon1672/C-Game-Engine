#include "ResourceManager.h"
#include <Engine/IO/MeshLoader.h>
#include <Engine/IO/QImageIO.h>
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Systems/Resources/Shaders/DefaultShaders.h>

IMPLEMENT_SINGLETON(ResourceManager);

Mesh * ResourceManager::addMesh(const char * name)
{
	geos.push_back(Mesh(name));
	MeshObjs.Register(geos.last());
	return &geos.last();
}
Mesh * ResourceManager::addMesh(const char * name, Neumont::ShapeData NUCrap)
{
	geos.push_back(Mesh(name));
	Mesh& ret = geos.last();
	for (uint i = 0; i < NUCrap.numVerts; i++) {
		auto& v = NUCrap.verts[i];
		ret.verts.push_back(Vert(v.position,v.color,v.position,glm::vec4(),v.uv));
	}
	for (uint i = 0; i < NUCrap.numIndices; i++) {
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
	geos.push_back(FileIO::loadMeshFromFile(filePath,name));
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
	ShaderProgramObjs.Register(shaders.last());
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

void ResourceManager::foreachOnAll(std::function<void(Resource&)> func)
{
	for (uint i = 0; i < shaders.size();  i++) func(shaders[i]);
	for (uint i = 0; i < geos.size();     i++) func(geos[i]);
	for (uint i = 0; i < textures.size(); i++) func(textures[i]);
}

TextureInfo * ResourceManager::add2DTexture(const char * name, QImage& image, GLenum type /*= GL_RGBA*/)
{
	return add2DTexture(name,image,type,type);
}
TextureInfo * ResourceManager::add2DTexture(const char * name, QImage& image, GLenum type, GLenum type2)
{
	return add2DTexture(name,image.bits(),image.byteCount(),image.width(),image.height(),type,type);
}
TextureInfo * ResourceManager::add2DTexture(const char * name, const char * filePath, bool flipHorz /*= false*/, bool flipVert /*= false*/)
{
	QImage data = FileIO::loadImage(filePath);
	if(flipVert || flipHorz) data = data.mirrored(flipHorz,flipVert);
	return add2DTexture(name,data);
}
TextureInfo * ResourceManager::add2DTexture(const char * name, std::string& filePath, bool flipHorz /*= false*/, bool flipVert /*= false*/)
{
	return add2DTexture(name,filePath.c_str(),flipHorz,flipVert);
}
TextureInfo * ResourceManager::add2DTexture(const char * name, ubyte * data, uint sizeofData, uint width, uint height, GLenum type, GLenum type2)
{
	textures.push_back(TextureInfo(name));
	TextureInfoObjs.Register(textures.last());
	textures.last().data = new ubyte[sizeofData];
	FileIO::myMemCopy(data,textures.last().data,sizeofData);

	textures.last().width  = width;
	textures.last().height = height;
	textures.last().type   = type;
	textures.last().type2  = type2;
	return &textures.last();
}


Script * ResourceManager::addScript_file(const char * name, const char * filePath)
{
	return addScript_src(name, FileIO::readFile(filePath));
}
Script * ResourceManager::addScript_file(const char * name, std::string filePath)
{
	return addScript_src(name, FileIO::readFile(filePath));
}
Script * ResourceManager::addScript_src (const char * name, const char * file)
{
	return addScript_src(name, std::string(file));
}
Script * ResourceManager::addScript_src (const char * name, std::string file)
{
	scripts.push_back(Script(name));
	ScriptObjs.Register(scripts.last());
	scripts.last().src = file;
	return &scripts.last();
}

ResourceManager::ResourceManager()
{
	defaultShader = addShader_src("basic Shader",DefaultShaders::VertexShader::DefaultVertShader(),DefaultShaders::FragShader::FragModelColor());
}

template<>
ShaderProgram * ResourceManager::getDefault()
{
	return defaultShader;
}

template<>
Mesh * ResourceManager::getDefault()
{
	return addMesh("Meshy");
}


#define RESOURCE_GET_METHODS_IMP(class_name, TYPE) \
	TYPE * class_name##::get##TYPE##(int id) { return (##TYPE##*)TYPE##Objs.getFirst(id); } \
	TYPE * class_name##::getFirst##TYPE##(std::string name)  { return getFirst##TYPE##(name.c_str()); } \
	TYPE * class_name##::getFirst##TYPE##(const char * name) { return (##TYPE##*)TYPE##Objs.getFirst(name); } \
	std::vector<TYPE*> class_name##::getAll##TYPE##(std::string name) { return Collections::RICVec<##TYPE##*>(TYPE##Objs.getAll(name.c_str())); }

RESOURCE_GET_METHODS_IMP(ResourceManager,Mesh);
RESOURCE_GET_METHODS_IMP(ResourceManager,ShaderProgram);
RESOURCE_GET_METHODS_IMP(ResourceManager,TextureInfo);
RESOURCE_GET_METHODS_IMP(ResourceManager,Script);
