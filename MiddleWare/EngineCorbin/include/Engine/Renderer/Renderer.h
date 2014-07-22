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
	Renderable myRenderables[1000];
	uint numOfRenderables;
	
	ShaderProgram allShaderProgs[10];
	uint numOfShaders;

	GeometryInfo geoInfo[1000];
	uint numOfGeoInfo;
	virtual void preDraw() {}
	virtual void renderableAdded(Renderable * justAdded) {}
public:
	ShaderProgram * mainShader;
	
	Renderer();
	void init();
	void reset();

	GeometryInfo * addGeometry( Neumont::ShapeData& toAdd, GLuint indexingMode = GL_TRIANGLES);
	GeometryInfo * addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode = GL_TRIANGLES);
	GeometryInfo * addGeometry( void * verts, uint sizeOfVerts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode = GL_TRIANGLES);

	virtual Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID=-1);
	void resetRenderables();

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

	uint addTexture(const char* fileName, bool flipHorz = false, bool flipVert = false);
	uint addTexture(ubyte * textureData, uint width, uint height, GLenum type = GL_RGBA);
	void draw(GeometryInfo& toDraw);
	void draw(Renderable& toDraw);
	void drawPrep(int width, int height);
};
