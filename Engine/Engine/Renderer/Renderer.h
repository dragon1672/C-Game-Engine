#pragma once

#include <ShapeData.h>
#include <Engine\Renderer\Renderable.h>
#include <Engine\Renderer\Geo\GeometryInfo.h>
#include <Engine\Renderer\Shader\ShaderProgram.h>
#include <Engine\Renderer\Shader\ShaderUniformPram.h>
#include <Engine\Renderer\ParameterType.h>
#include <Engine\unsigned.h>
#include <Engine/Tools/ConstVector.h>

#include <Engine/Renderer/TextureInfo.h>

#include <ExportHeader.h>


class ENGINE_SHARED Renderer {
private:
	ConstVector<Renderable> myRenderables;
	ConstVector<ShaderProgram> allShaderProgs;
	ConstVector<GeometryInfo> geoInfo;
	ConstVector<TextureInfo> textures;

	virtual void preDraw() {}
	virtual void renderableAdded(Renderable * justAdded) {justAdded;}
public:
	ShaderProgram * mainShader;
	
	Renderer();
	~Renderer();
	void init();
	void reset();

	GeometryInfo * addGeometry( Neumont::ShapeData& toAdd, GLuint indexingMode = GL_TRIANGLES);
	GeometryInfo * addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode = GL_TRIANGLES);
	GeometryInfo * addGeometry( void * verts, uint sizeOfVerts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode = GL_TRIANGLES);

	virtual Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID=-1);

	ShaderProgram * addShader();
	ShaderProgram * addShader(const char * vertexShader, const char * fragShader);
	void passDataDownAllShaders_force();
	void passDataDownAllShaders_try();
	void resetAllShaders_validPush();

	uint getNumOfShaders();
	uint getNumOfRenderables();
	uint getNumOfGeo();
	ShaderProgram * getShader(uint index);
	Renderable* getRenderable(uint index);
	GeometryInfo* getGeometry(uint index);

	TextureInfo * add2DTexture(QImage& image, GLenum type = GL_RGBA);
	TextureInfo * add2DTexture(QImage& image, GLenum type, GLenum type2);
	TextureInfo * add2DTexture(const char * filePath, bool flipHorz = false, bool flipVert = false);
	TextureInfo * add2DTexture(QString& filePath, bool flipHorz = false, bool flipVert = false);
	TextureInfo * add2DTexture(ubyte * data, uint width, uint height, GLenum type = GL_RGBA);
	TextureInfo * add2DTexture(ubyte * data, uint width, uint height, GLenum type, GLenum type2);
	TextureInfo * add2DTexture(ImageData& imageData);

	TextureInfo * addCubeTexture(QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	TextureInfo * addCubeTexture(const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ);
	TextureInfo * addCubeTexture(QString& directory,QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	TextureInfo * addCubeTexture(const char * directory,const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ);
	TextureInfo * addCubeTexture(ImageData& posX,ImageData& negX,ImageData& posY,ImageData& negY,ImageData& posZ,ImageData& negZ);
	TextureInfo * addCubeTexture(QImage& posX,QImage& negX,QImage& posY,QImage& negY,QImage& posZ,QImage& negZ);

	void draw(GeometryInfo * toDraw);
	void draw(GeometryInfo& toDraw);
	void draw(Renderable * toDraw);
	void draw(Renderable& toDraw);
	void drawPrep(int width, int height);
};
