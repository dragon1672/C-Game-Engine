#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <Engine/Tools/ConstVector.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Systems/Resources/Mesh.h>
#include <Engine/Systems/Resources/ShaderProgram.h>
#include <Engine/Systems/Resources/Script.h>
#include <Engine/Systems/ObjectManager.h>
#include <ShapeData.h>
#include <functional>
#include <ExportHeader.h>
#include <Engine/TypeDefs.h>

#define resourceManager ResourceManager::getInstance()

class ENGINE_SHARED ResourceManager : public Resource {
	DEFINE_SINGLETON(ResourceManager);
private:
	ConstVector<ShaderProgram> shaders;
	ObjectManager ShaderProgramObjs;
	ConstVector<Mesh> geos;
	ObjectManager MeshObjs;
	ConstVector<TextureInfo> textures;
	ObjectManager TextureInfoObjs;
	ConstVector<Script> scripts;
	ObjectManager ScriptObjs;
	void foreachOnAll(std::function<void(Resource&)> func);

	ShaderProgram * defaultShader;
	std::string workingDir;
public:
	ResourceManager();

	std::string WorkingDir() const { return workingDir; }
	void WorkingDir(std::string val) { workingDir = val; }

	void loadNeumontStuff();

	Mesh * addMesh(std::string name);
	Mesh * addMesh(std::string name, Neumont::ShapeData NUCrap);
	Mesh * addMesh(std::string name, std::string  filePath, bool useRelPath = true);
	Mesh * addMesh(std::string name, const char * filePath, bool useRelPath = true);

	ShaderProgram * addShader_file(std::string name, const char * vertFilePath, const char * fragFilePath, bool useRelPath = true);
	ShaderProgram * addShader_file(std::string name, std::string  vertFilePath, std::string  fragFilePath, bool useRelPath = true);
	ShaderProgram * addShader_src (std::string name, std::string vert, std::string frag);
	ShaderProgram * addShader_src (std::string name, const char * vert, const char * frag);

	TextureInfo * add2DTexture(std::string name, QImage& image, GLenum type = GL_RGBA);
	TextureInfo * add2DTexture(std::string name, QImage& image, GLenum type, GLenum type2);
	TextureInfo * add2DTexture(std::string name, const char * filePath, bool useRelPath = true, bool flipHorz = false, bool flipVert = false);
	TextureInfo * add2DTexture(std::string name, std::string& filePath, bool useRelPath = true, bool flipHorz = false, bool flipVert = false);
	TextureInfo * add2DTexture(std::string name, ubyte * data, uint sizeofData, uint width, uint height, GLenum type, GLenum type2);

	Script * addScript_file(const char * filePath, bool useRelPath = true);
	Script * addScript_file(std::string  filePath, bool useRelPath = true);
	Script * addScript_src (std::string file);
	Script * addScript_src (const char * file);

	Mesh *          duplicate(Mesh * toDup);
	ShaderProgram * duplicate(ShaderProgram * toDup);
	//TextureInfo *   duplicate(TextureInfo * toDup);
	//Script *        duplicate(Script * toDup);
	
	
	
	

	template<typename T> T* getDefault() { return nullptr; }
	template<> Mesh * getDefault();
	template<> ShaderProgram * getDefault();


#define RESOURCE_GET_METHODS(TYPE) \
	TYPE * get##TYPE##(int id); \
	TYPE * getFirst##TYPE##(const char * name); \
	TYPE * getFirst##TYPE##(std::string name); \
	std::vector<TYPE*> getAll##TYPE##(std::string name); \
	std::vector<TYPE*> getAll##TYPE##()

	RESOURCE_GET_METHODS(Mesh);
	RESOURCE_GET_METHODS(ShaderProgram);
	RESOURCE_GET_METHODS(TextureInfo);
	RESOURCE_GET_METHODS(Script);

	void init();

	void PassDownToHardWare();

	void update();

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();
	void shutdown();

	virtual void Save(Stream& s);

	virtual void Load(Stream& s);
	void ImportPack(Stream& s);

};