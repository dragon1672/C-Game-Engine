#pragma once

#include <ShapeData.h>
#include <Engine\Renderer\Renderable.h>
#include <Engine\Renderer\Geo\GeometryInfo.h>
#include <Engine\Renderer\Shader\ShaderProgram.h>
#include <Engine\Renderer\Shader\ShaderUniformPram.h>
#include <Engine\Renderer\ParameterType.h>

#include <ExportHeader.h>


class ENGINE_SHARED Renderer {
public:
	ShaderProgram * mainShader;
protected:
	Renderable myRenderables[1000];
	uint numOfRenderables;
	
	ShaderProgram allShaderProgs[10];
	uint numOfShaders;

	GeometryInfo geoInfo[1000];
	uint numOfGeoInfo;

	virtual void preDraw() {}
public:
	Renderer();
	void init();
	void reset();

	GeometryInfo * addGeometry( Neumont::ShapeData& toAdd, GLuint indexingMode);
	GeometryInfo * addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode);
	GeometryInfo * addGeometry( void * verts, uint sizeOfVerts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode);

	Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID);
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

	uint addTexture(const char* fileName);
	void draw(GeometryInfo& toDraw);
	void draw(Renderable& toDraw);
	void drawPrep(int width, int height);
};
