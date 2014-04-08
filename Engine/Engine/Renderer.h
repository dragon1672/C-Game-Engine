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

	GeometryInfo * addGeometry( Neumont::ShapeData& toAdd, GLuint indexingMode);
	GeometryInfo * addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode);

	Renderable* addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID);

	ShaderProgram * addShader();
	ShaderProgram * addShader(const char * vertexShader, const char * fragShader);
	void passDataDownAllShaders(); // might bite me in the butt later

	uint getNumOfShaders();
	uint getNumOfRenderables();
	uint getNumOfGeo();
	ShaderProgram * getShader(uint index);
	Renderable* getRenderable(uint index);
	GeometryInfo* getGeometry(uint index);

	//not required
	void addStreamedParameter(GeometryInfo * geoID, uint layoutLocation, ParameterType parameterType, uint bufferOffset, uint bufferStride);

	//not required
	void addRenderableUniformParameter(Renderable* renderable, const char* name, ParameterType parameterType, const float* value);

	uint addTexture(const char* fileName);
	void draw(GeometryInfo& toDraw);
	void draw(Renderable& toDraw);
	inline void drawPrep(int width, int height) {
		glClearColor(.1f,.1f,.1f,1);
		glViewport(0,0,width,height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};
