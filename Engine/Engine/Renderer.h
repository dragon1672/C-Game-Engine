#pragma once

#include "Renderable.h"
#include "GeometryInfo.h"
#include "ShaderProgram.h"
#include "ShaderUniformPram.h"
#include "ParameterType.h"
#include <ShapeData.h>

#include "ExportHeader.h"


class ENGINE_SHARED Renderer {
private:
	Renderable myRenderables[200];
	uint numOfRenderables;
public:
	ShaderProgram * mainShader;
private:
	ShaderProgram allShaderProgs[10];
	uint numOfShaders;

	GeometryInfo geoInfo[100];
	uint numOfGeoInfo;
public:
	void init();
	void reset();

	GeometryInfo * addGeometry( Neumont::ShapeData& toAdd, GLuint indexingMode);
	GeometryInfo * addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode);

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
