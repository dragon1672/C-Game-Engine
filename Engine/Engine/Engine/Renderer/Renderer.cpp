#include <GL/glew.h>

#include <Engine\Renderer\Renderer.h>
#include <Qt\qdebug.h>
#include <Engine\Defines\Vectors.h>

//encoded with (char + i % 5
const char * thankYouMessage = "_xazcw`yb{!\"01%Ujdrp!{ry%gqu$ztkqk%Bpwlto{#Gtsdlr,t\"Uiseguiw!/0$cw`yb{_xaz";

Renderer::Renderer() {
	QDebug deb = qDebug().nospace();
	for (int i = 0; i < strlen(thankYouMessage); i++)
	{
		deb << (char)(thankYouMessage[i] - i%5 - 1);
	}
	deb << "\n\n";
}
void            Renderer::init() {
	mainShader = addShader();
}
Renderer::~Renderer() {
	reset();
}
void            Renderer::reset() {
	CLEAR_VECTOR(geoInfo);
	CLEAR_VECTOR_WITH_CALL(myRenderables,reset);
	CLEAR_VECTOR(allShaderProgs);
}
GeometryInfo  * Renderer::addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode) {
	GeometryInfo * ret = new GeometryInfo();
	geoInfo.push_back(ret);
	ret->init(verts,numVerts,indices,numIndices,indexingMode);
	return ret;
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
	Renderable * ret = new Renderable();
	myRenderables.push_back(ret);
	ret->init(whatGeometry,howShaders,true,textureID);
	renderableAdded(ret);
	return ret;
}
ShaderProgram * Renderer::addShader() {
	ShaderProgram * ret = new ShaderProgram();
	allShaderProgs.push_back(ret);
	ret -> startup();
	return ret;
}
ShaderProgram * Renderer::addShader(const char * vertexShader, const char * fragShader) {
	ShaderProgram * ret = addShader();
	ret->buildBasicProgram(vertexShader,fragShader);
	return ret;
}
void            Renderer::passDataDownAllShaders_force() {
	for (uint i = 0; i < allShaderProgs.size(); i++)
	{
		allShaderProgs[i]->passSavedUniforms_force();
	}
}
void            Renderer::passDataDownAllShaders_try() {
	for (uint i = 0; i < allShaderProgs.size(); i++)
	{
		allShaderProgs[i]->passSavedUniforms_try();
	}
}
void            Renderer::resetAllShaders_validPush() {
	for (uint i = 0; i < allShaderProgs.size(); i++)
	{
		allShaderProgs[i]->resetValidPush();
	}
}
uint            Renderer::getNumOfShaders()      { return allShaderProgs.size(); }
uint            Renderer::getNumOfRenderables()  { return myRenderables.size();  }
uint            Renderer::getNumOfGeo()          { return geoInfo.size();        }

ShaderProgram * Renderer::getShader(uint index) { return allShaderProgs[index];    }
Renderable    * Renderer::getRenderable(uint index) { return myRenderables[index]; }
GeometryInfo  * Renderer::getGeometry(uint index) { return geoInfo[index];         }

GLuint          Renderer::addTexture(QImage image, GLenum type) {
	return ShaderProgram::load2DTexture(image,type);
}
GLuint          Renderer::addTexture(QImage image, GLenum type, GLenum type2) {
	return ShaderProgram::load2DTexture(image,type,type2);
}
GLuint          Renderer::addTexture(const char * filePath, bool flipHorz, bool flipVert) {
	return ShaderProgram::load2DTexture(QString(filePath),flipHorz,flipVert);
}
GLuint          Renderer::addTexture(ubyte * data, uint width, uint height, GLenum type) {
	return ShaderProgram::load2DTexture(data,width,height,type);
}
GLuint          Renderer::addTexture(ubyte * data, uint width, uint height, GLenum type, GLenum type2) {
	return ShaderProgram::load2DTexture(data,width,height,type,type2);
}
GLuint          Renderer::addTexture(ShaderProgram::ImageData& imageData) {
	return ShaderProgram::load2DTexture(imageData);
}

GLuint          Renderer::addCubeTexture(QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ) {
	return ShaderProgram::loadCubeTexture(posX,negX,posY,negY,posZ,negZ);
}
GLuint          Renderer::addCubeTexture(QString& directory,QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ) {
	return ShaderProgram::loadCubeTexture(directory,posX,negX,posY,negY,posZ,negZ);
}
GLuint          Renderer::addCubeTexture(const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ) {
	return ShaderProgram::loadCubeTexture(QString(posX),QString(negX),QString(posY),QString(negY),QString(posZ),QString(negZ));
}
GLuint          Renderer::addCubeTexture(const char * directory,const char * posX,const char * negX,const char * posY,const char * negY,const char * posZ,const char * negZ) {
	return ShaderProgram::loadCubeTexture(QString(directory),QString(posX),QString(negX),QString(posY),QString(negY),QString(posZ),QString(negZ));
}
GLuint          Renderer::addCubeTexture(ShaderProgram::ImageData& posX,ShaderProgram::ImageData& negX,ShaderProgram::ImageData& posY,ShaderProgram::ImageData& negY,ShaderProgram::ImageData& posZ,ShaderProgram::ImageData& negZ) {
	return ShaderProgram::loadCubeTexture(posX,negX,posY,negY,posZ,negZ);
}
GLuint          Renderer::addCubeTexture(QImage& posX,QImage negX,QImage& posY,QImage negY,QImage& posZ,QImage negZ) {
	return ShaderProgram::loadCubeTexture(posX,negX,posY,negY,posZ,negZ);
}

void            Renderer::draw(Renderable& toDraw) {
	if(toDraw.visible) {
		toDraw.transformData.updateMatrix();
		toDraw.howShader->useProgram();
		toDraw.howShader->passSavedUniforms_try();
		toDraw.passUniformsDownDown();
		draw(*toDraw.whatGeo);
	}
}
void            Renderer::draw(GeometryInfo& toDraw) {
	preDraw();
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