#include "ResourceManager.h"
#include <Engine/IO/MeshLoader.h>
#include <Engine/IO/QImageIO.h>
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Systems/Resources/Shaders/DefaultShaders.h>
#include <Engine/DebugTools/DebugMemHeader.h>
#include <ShapeGenerator.h>


IMPLEMENT_SINGLETON(ResourceManager);

Mesh * ResourceManager::addMesh(std::string name)
{
	geos.push_back(Mesh(name));
	MeshObjs.Register(geos.back());
	return &geos.back();
}
Mesh * ResourceManager::addMesh(std::string name, Neumont::ShapeData NUCrap)
{
	geos.push_back(Mesh(name));
	Mesh& ret = geos.back();
	for (uint i = 0; i < NUCrap.numVerts; i++) {
		auto& v = NUCrap.verts[i];
		ret.verts.push_back(Vert(v.position,v.color,v.position,glm::vec4(),v.uv));
	}
	for (uint i = 0; i < NUCrap.numIndices; i++) {
		ret.indices.push_back(NUCrap.indices[i]);
	}
	MeshObjs.Register(geos.back());
	return &geos.back();
}
Mesh * ResourceManager::addMesh(std::string name, std::string filePath)
{
	return addMesh(filePath.c_str());
}
Mesh * ResourceManager::addMesh(std::string name, const char * filePath)
{
	geos.push_back(FileIO::loadMeshFromFile(filePath,name));
	MeshObjs.Register(geos.back());
	return &geos.back();
}
ShaderProgram * ResourceManager::addShader_file(std::string name, const char * vertFilePath, const char * fragFilePath)
{
	return addShader_file(name,std::string(vertFilePath),std::string(fragFilePath));
}
ShaderProgram * ResourceManager::addShader_file(std::string name, std::string vertFilePath, std::string fragFilePath)
{
	return addShader_src(name, FileIO::readFile(workingDir + vertFilePath),FileIO::readFile(workingDir + fragFilePath));
}
ShaderProgram * ResourceManager::addShader_src (std::string name, std::string vert, std::string frag)
{
	return addShader_src(name, vert.c_str(),frag.c_str());
}
ShaderProgram * ResourceManager::addShader_src (std::string name, const char * vert, const char * frag)
{
	shaders.push_back(ShaderProgram(name));
	ShaderProgramObjs.Register(shaders.back());
	shaders.back().buildBasicProgram(vert,frag);
	return &shaders.back();
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
	for (uint i = 0; i < scripts.size();  i++) func(scripts[i]);
}

TextureInfo * ResourceManager::add2DTexture(std::string name, QImage& image, GLenum type /*= GL_RGBA*/)
{
	return add2DTexture(name,image,type,type);
}
TextureInfo * ResourceManager::add2DTexture(std::string name, QImage& image, GLenum type, GLenum type2)
{
	return add2DTexture(name,image.bits(),image.byteCount(),image.width(),image.height(),type,type);
}
TextureInfo * ResourceManager::add2DTexture(std::string name, const char * filePath, bool flipHorz /*= false*/, bool flipVert /*= false*/)
{
	return add2DTexture(name,std::string(filePath),flipHorz,flipVert);
}
TextureInfo * ResourceManager::add2DTexture(std::string name, std::string& filePath, bool flipHorz /*= false*/, bool flipVert /*= false*/)
{
	QImage data = FileIO::loadImage(workingDir + filePath);
	if(flipVert || flipHorz) data = data.mirrored(flipHorz,flipVert);
	return add2DTexture(name,data);
}
TextureInfo * ResourceManager::add2DTexture(std::string name, ubyte * data, uint sizeofData, uint width, uint height, GLenum type, GLenum type2)
{
	textures.push_back(TextureInfo(name));
	TextureInfoObjs.Register(textures.back());
	textures.back().data = new ubyte[sizeofData];
	FileIO::myMemCopy(data,textures.back().data,sizeofData);

	textures.back().width  = width;
	textures.back().height = height;
	textures.back().type   = type;
	textures.back().type2  = type2;
	return &textures.back();
}


Script * ResourceManager::addScript_file(const char * filePath)
{
	return addScript_file(std::string(filePath));
}
Script * ResourceManager::addScript_file(std::string filePath)
{
	return addScript_src(FileIO::readFile(workingDir + filePath));
}
Script * ResourceManager::addScript_src (const char * file)
{
	return addScript_src(std::string(file));
}
Script * ResourceManager::addScript_src (std::string file)
{
	scripts.push_back(Script());
	scripts.back().Src(file);
	scripts.back().updateName();
	ScriptObjs.Register(scripts.back());
	return &scripts.back();
}

ResourceManager::ResourceManager()
{
	defaultShader = nullptr;
}

template<>
ShaderProgram * ResourceManager::getDefault()
{
	if(defaultShader == nullptr) { defaultShader = addShader_src("basic Shader",DefaultShaders::VertexShader::DefaultVertShader(),DefaultShaders::FragShader::FragModelColor()); }
	return defaultShader;
}

template<>
Mesh * ResourceManager::getDefault()
{
	return addMesh("Meshy");
}

bool ResourceManager::isValid()
{
	return true;
}

std::vector<std::string> ResourceManager::getErrors()
{
	return std::vector<std::string>();
}

void ResourceManager::shutdown()
{
	foreachOnAll([](Resource&r){r.shutdown();});
}
#include <Engine/Systems/Resources/Mesh.h>
void ResourceManager::loadNeumontStuff()
{
	Mesh * tmp;
	tmp = addMesh("NU_Cube",Neumont::ShapeGenerator::makeCube());
	tmp = addMesh("NU_Sphere",Neumont::ShapeGenerator::makeSphere(30));
	tmp->initUVData();
	tmp = addMesh("NU_Arrow",Neumont::ShapeGenerator::makeArrow());
	tmp = addMesh("NU_SmallPlane",Neumont::ShapeGenerator::makePlane(2));
	tmp = addMesh("NU_Plane",Neumont::ShapeGenerator::makePlane(10));
	tmp = addMesh("NU_Torus",Neumont::ShapeGenerator::makeTorus(20));
	tmp->initUVData();
	tmp->setRandomColor(1);
	tmp = addMesh("NU_TeaPot",Neumont::ShapeGenerator::makeTeapot(30,glm::mat4()));
	tmp->setRandomColor(4);
	tmp->rotate(-90,0,0);
}

Mesh * ResourceManager::duplicate(Mesh * toDup)
{
	auto ret = addMesh(toDup->Name()+"_dup");
	*ret = *toDup; // copy!
	return ret;
}

ShaderProgram * ResourceManager::duplicate(ShaderProgram * toDup)
{
	shaders.add(*toDup);
	shaders.back().Name(toDup->Name()+"_dup");
	ShaderProgramObjs.Register(shaders.back());
	return &shaders.back();
}

#define RESOURCE_GET_METHODS_IMP(class_name, TYPE) \
	TYPE * class_name##::get##TYPE##(int id) { return (##TYPE##*)TYPE##Objs.getFirst(id); } \
	TYPE * class_name##::getFirst##TYPE##(std::string name)  { return getFirst##TYPE##(name.c_str()); } \
	TYPE * class_name##::getFirst##TYPE##(const char * name) { return (##TYPE##*)TYPE##Objs.getFirst(name); } \
	std::vector<TYPE*> class_name##::getAll##TYPE##(std::string name) { return Collections::RICVec<##TYPE##*>(TYPE##Objs.getAll(name.c_str())); } \
	std::vector<TYPE*> class_name##::getAll##TYPE##() { return Collections::RICVec<##TYPE##*>(TYPE##Objs.getAll()); } 

RESOURCE_GET_METHODS_IMP(ResourceManager,Mesh);
RESOURCE_GET_METHODS_IMP(ResourceManager,ShaderProgram);
RESOURCE_GET_METHODS_IMP(ResourceManager,TextureInfo);
RESOURCE_GET_METHODS_IMP(ResourceManager,Script);
