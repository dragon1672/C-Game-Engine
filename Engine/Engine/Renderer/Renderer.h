#pragma once

#include <ShapeData.h>
#include <Engine\Renderer\Renderable.h>
#include <Engine\Renderer\Geo\GeometryInfo.h>
#include <Engine\Renderer\Shader\ShaderProgram.h>
#include <Engine\Renderer\Shader\ShaderUniformPram.h>
#include <Engine\Renderer\ParameterType.h>
#include <Engine\unsigned.h>

#include <ExportHeader.h>


class ENGINE_SHARED Renderer {
private:
	std::vector<Renderable *> myRenderables;
	std::vector<ShaderProgram *> allShaderProgs;
	std::vector<GeometryInfo *> geoInfo;

	virtual void preDraw() {}
	virtual void renderableAdded(Renderable * justAdded) {}
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

	GLuint addTexture(QImage image, GLenum type = GL_RGBA);
	GLuint addTexture(QImage image, GLenum type, GLenum type2);
	GLuint addTexture(const char * filePath, bool flipHorz = false, bool flipVert = false);
	GLuint addTexture(ubyte * data, uint width, uint height, GLenum type = GL_RGBA);
	GLuint addTexture(ubyte * data, uint width, uint height, GLenum type, GLenum type2);
	GLuint addTexture(ShaderProgram::ImageData& imageData);

	GLuint addCubeTexture(QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	GLuint addCubeTexture(const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ);
	GLuint addCubeTexture(QString& directory,QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ);
	GLuint addCubeTexture(const char * directory,const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ);
	GLuint addCubeTexture(ShaderProgram::ImageData& posX,ShaderProgram::ImageData& negX,ShaderProgram::ImageData& posY,ShaderProgram::ImageData& negY,ShaderProgram::ImageData& posZ,ShaderProgram::ImageData& negZ);
	GLuint addCubeTexture(QImage& posX,QImage negX,QImage& posY,QImage negY,QImage& posZ,QImage negZ);

	void draw(GeometryInfo& toDraw);
	void draw(Renderable& toDraw);
	void drawPrep(int width, int height);
};
