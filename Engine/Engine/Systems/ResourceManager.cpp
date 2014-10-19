#include "ResourceManager.h"
#include <Engine/IO/MeshLoader.h>
#include <Engine/IO/QImageIO.h>

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
	TextureObjs.Register(textures.last());
	textures.last().data = new ubyte[sizeofData];
	FileIO::myMemCopy(data,textures.last().data,sizeofData);

	textures.last().width  = width;
	textures.last().height = height;
	textures.last().type   = type;
	textures.last().type2  = type2;
	return &textures.last();
}
