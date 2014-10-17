#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Tools/Timer.h>
#include <Engine/Renderer/TextureInfo.h>
#include <Engine/Defines/SingletonsDefine.h>

#include <Engine/Tools/ConstVector.h>
#include <Engine/Renderer/Geo/Mesh.h>
#include <ExportHeader.h>

class ENGINE_SHARED GameObjectManager {
private:
	ConstVector<Entity> entities;
	ConstVector<TextureInfo> textures;
	ConstVector<ShaderProgram> allShaderProgs;
	ConstVector<Mesh> geos;
	
	Renderer renderer;
	bool active;

	void passDataDownAllShaders_force();
	void passDataDownAllShaders_try();
	void resetAllShaders_validPush();
public:

	//add
	Entity * AddEntity(const char * name = "GameObject");
	Mesh * addMesh();
	Mesh * addMesh(Neumont::ShapeData& toAdd, GLuint indexingMode = GL_TRIANGLES);
	Mesh * addMesh(const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode = GL_TRIANGLES);
	Mesh * addMesh(void * verts, uint sizeOfVerts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode = GL_TRIANGLES);

	ShaderProgram * addShader();
	ShaderProgram * addShader(const char * vertexShader, const char * fragShader);

	TextureInfo * add2DTexture(const char * filePath, bool flipHorz = false, bool flipVert = false);
	TextureInfo * add2DTexture(QString& filePath, bool flipHorz = false, bool flipVert = false);

	TextureInfo * addCubeTexture(QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	TextureInfo * addCubeTexture(const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ);
	TextureInfo * addCubeTexture(QString& directory,QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	TextureInfo * addCubeTexture(const char * directory,const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ);

	GameObjectManager();
	bool init();
	bool shutdown();
	void update();
	void paint();
};