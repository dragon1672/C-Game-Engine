#include <GL/glew.h>

#include <Engine\Renderer\Renderer.h>

void            Renderer::init() {
	glEnable(GL_DEPTH_TEST);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
	numOfRenderables = 0;
	numOfShaders = 0;
	numOfGeoInfo = 0;
	mainShader = addShader();
}
void            Renderer::reset() {
	//wipe renderables
	//clear geo from hardware
	//clear geo infos
	//clear shaders
}
GeometryInfo  * Renderer::addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode) {
	int id = numOfGeoInfo++;
	geoInfo[id].init(verts,numVerts,indices,numIndices,indexingMode);
	return &geoInfo[id];
}
GeometryInfo  * Renderer::addGeometry( Neumont::ShapeData& toAdd, GLuint indexingMode) {
	GeometryInfo * ret = addGeometry(toAdd.verts,toAdd.numVerts,toAdd.indices,toAdd.numIndices,indexingMode);
	ret -> NU_VertexStreamedPosition(0);
	ret -> NU_VertexStreamedColor(1);
	ret -> NU_VertexStreamedNormal(2);
	ret -> NU_VertexStreamedUv(3);
	return ret;
}
Renderable    * Renderer::addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID) {
	int id = numOfRenderables++;
	myRenderables[id].init(whatGeometry,howShaders,true,textureID);
	return &myRenderables[id];
}
void			Renderer::resetRenderables() {
	for (uint i = 0; i < numOfRenderables; i++)
	{
		myRenderables[i].reset();
	}
	numOfRenderables = 0;
}
ShaderProgram * Renderer::addShader() {
	ShaderProgram * ret = &allShaderProgs[numOfShaders++];
	ret -> startup();
	return ret;
}
ShaderProgram * Renderer::addShader(const char * vertexShader, const char * fragShader) {
	ShaderProgram * ret = addShader();
	ret->buildBasicProgram(vertexShader,fragShader);
	return ret;
}
void            Renderer::passDataDownAllShaders_force() {
	for (uint i = 0; i < numOfShaders; i++)
	{
		allShaderProgs[i].passSavedUniforms_force();
	}
}
void            Renderer::passDataDownAllShaders_try() {
	for (uint i = 0; i < numOfShaders; i++)
	{
		allShaderProgs[i].passSavedUniforms_try();
	}
}
void            Renderer::resetAllShaders_validPush() {
	for (uint i = 0; i < numOfShaders; i++)
	{
		allShaderProgs[i].resetValidPush();
	}
}
uint            Renderer::getNumOfShaders()      { return numOfShaders;     }
uint            Renderer::getNumOfRenderables()  { return numOfRenderables; }
uint            Renderer::getNumOfGeo()          { return numOfGeoInfo;     }
ShaderProgram * Renderer::getShader(uint index) { return &allShaderProgs[index]; }
Renderable    * Renderer::getRenderable(uint index) { return &myRenderables[index];  }
GeometryInfo  * Renderer::getGeometry(uint index) { return &geoInfo[index];        }
uint            Renderer::addTexture(const char* fileName) {
	return ShaderProgram::load2DTexture(fileName);
}
void            Renderer::draw(Renderable& toDraw) {
	if(toDraw.visible) {
		toDraw.howShader->useProgram();
		toDraw.howShader->passSavedUniforms_try();
		toDraw.passUniformsDownDown();
		draw(*toDraw.whatGeo);
	}
}
void            Renderer::draw(GeometryInfo& toDraw) {
	glBindVertexArray(toDraw.vertexArrayObjectID);
	glBindBuffer(toDraw.bufferInformation.bufferID,GL_ARRAY_BUFFER);
	glBindBuffer(toDraw.bufferInformation.bufferID,GL_ELEMENT_ARRAY_BUFFER);
	glDrawElements(toDraw.indexingMode,toDraw.numIndices,GL_UNSIGNED_SHORT,(void*)toDraw.indicesOffset());
}
void            Renderer::drawPrep(int width, int height) {
	glClearColor(.1f,.1f,.1f,1);
	glViewport(0,0,width,height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}