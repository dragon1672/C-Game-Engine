#include <GL/glew.h>

#include <Engine\Renderer\Renderer.h>
#include <Qt\qdebug.h>
#include <Engine\Defines\Vectors.h>
#include <Qt\qapplication.h>
#include <Qt\qfile.h>

#define GL_RGBA 0x1908

#include <Engine/DebugTools/DebugMemHeader.h>

//encoded with (char + i % 5
const char * thankYouMessage = "_xazcw`yb{!\"01%Ujdrp!{ry%gqu$ztkqk%Bpwlto{#Gtsdlr,t\"Uiseguiw!/0$cw`yb{_xaz";

Renderer::Renderer() {
	QDebug deb = qDebug().nospace();
	for (uint i = 0; i < strlen(thankYouMessage); i++)
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
	//CLEAR_VECTOR(geoInfo);
	for (uint i = 0; i < myRenderables.size(); i++) myRenderables[i].reset();
	//CLEAR_VECTOR_WITH_CALL(myRenderables,reset);
	//CLEAR_VECTOR(allShaderProgs);
}
GeometryInfo  * Renderer::addGeometry( const Neumont::Vertex* verts, uint numVerts,  ushort* indices, uint numIndices, GLuint indexingMode) {
	geoInfo.add(GeometryInfo());
	GeometryInfo * ret = &geoInfo.last();
	ret->init(verts,numVerts,indices,numIndices,indexingMode);
	return ret;
}
GeometryInfo  * Renderer::addGeometry( Neumont::ShapeData& toAdd, GLuint indexingMode) {
	GeometryInfo * ret = addGeometry(toAdd.verts,toAdd.numVerts,toAdd.indices,toAdd.numIndices,indexingMode);
	int data[] = { 3,4,3,2 };
	ret->addStreamedParameters(data,sizeof(data)/sizeof(*data));
	return ret;
}
Renderable    * Renderer::addRenderable(GeometryInfo * whatGeometry, ShaderProgram * howShaders, GLuint textureID) {
	myRenderables.add(Renderable());
	Renderable * ret = &myRenderables.last();
	ret->init(whatGeometry,howShaders,true,textureID);
	renderableAdded(ret);
	return ret;
}
ShaderProgram * Renderer::addShader() {
	allShaderProgs.add(ShaderProgram());
	ShaderProgram * ret = &allShaderProgs.last();
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
		allShaderProgs[i].passSavedUniforms_force();
	}
}
void            Renderer::passDataDownAllShaders_try() {
	for (uint i = 0; i < allShaderProgs.size(); i++)
	{
		allShaderProgs[i].passSavedUniforms_try();
	}
}
void            Renderer::resetAllShaders_validPush() {
	for (uint i = 0; i < allShaderProgs.size(); i++)
	{
		allShaderProgs[i].resetValidPush();
	}
}
uint            Renderer::getNumOfShaders()      { return allShaderProgs.size(); }
uint            Renderer::getNumOfRenderables()  { return myRenderables.size();  }
uint            Renderer::getNumOfGeo()          { return geoInfo.size();        }

ShaderProgram * Renderer::getShader(uint index) { return &allShaderProgs[index];    }
Renderable    * Renderer::getRenderable(uint index) { return &myRenderables[index]; }
GeometryInfo  * Renderer::getGeometry(uint index) { return &geoInfo[index];         }

namespace {

	QString formatFileName(QString& fileName) {
		QString formatedName = fileName.replace(QRegExp("[_]")," ");
		formatedName = formatedName.remove(".jpg",Qt::CaseInsensitive);
		formatedName = formatedName.remove(".png",Qt::CaseInsensitive);
		int lastSlash = formatedName.lastIndexOf('/');
		formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
		lastSlash = formatedName.lastIndexOf('\\');
		formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
		return formatedName;
	}

	QImage getImageFromFile(QString& fileName, bool flipHorz, bool flipVert) {
		QImage myTexture = QGLWidget::convertToGLFormat(QImage(fileName).mirrored(flipHorz,flipVert));

		if(myTexture.isNull()) {
			qDebug() << "attempt to load " << fileName << " failed";
			assert(false);
		} else {
			QString formatedName = fileName.replace(QRegExp("[_]")," ");
			formatedName = formatedName.remove(".jpg",Qt::CaseInsensitive);
			formatedName = formatedName.remove(".png",Qt::CaseInsensitive);
			int lastSlash = formatedName.lastIndexOf('/');
			formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
			lastSlash = formatedName.lastIndexOf('\\');
			formatedName = formatedName.mid(lastSlash,formatedName.size()-lastSlash);
			qDebug() << "Texture Loaded ( " << myTexture.width() << "x" << myTexture.width() << " ): " << formatFileName(fileName);
		}

		return myTexture;
	}

	void update2DTexture(uint textureID, uint slot, ubyte * data, uint width, uint height, GLenum fileType, GLenum fileType2) {
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0+slot);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D,0, fileType, width, height, 0, fileType2, GL_UNSIGNED_BYTE, data);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	void update2DTexture(uint textureID, uint slot, QImage& image, GLenum type, GLenum type2) {
		update2DTexture(textureID,slot, image.bits(),image.width(),image.height(), type, type2);
	}
	void update2DTexture(uint textureID, uint slot, QImage& image, GLenum type = GL_RGBA) {
		update2DTexture(textureID,slot, image.bits(),image.width(),image.height(), type, type);
	}
	void update2DTexture(uint textureID, uint slot, QString& fileName, bool flipHorz = false, bool flipVert = false) {
		QString filePath = /**/QCoreApplication::applicationDirPath() + /**/fileName;
		QFile tempFile(filePath);
		if(tempFile.exists()) {
			QImage data = getImageFromFile(filePath,flipHorz,flipVert);
			update2DTexture(textureID,slot, data);
		} else {
			qDebug() << "Invalid file path " << formatFileName(filePath) << " Texture not loaded";
			assert(false);
		}
	}
	void update2DTexture(uint textureID, uint slot, ubyte * data, uint width, uint height, GLenum fileType) {
		update2DTexture(textureID,slot,data,width,height,fileType,fileType);
	}
	void update2DTexture(uint textureID, uint slot, ImageData& imageData) {
		update2DTexture(textureID,slot, imageData.data,imageData.width,imageData.height,imageData.type, imageData.type2 == -1 ? imageData.type : imageData.type2);
	}
	
}

TextureInfo * Renderer::add2DTexture(QImage& image, GLenum type) {
	return add2DTexture(image,type,type);
}
TextureInfo * Renderer::add2DTexture(QImage& image, GLenum type, GLenum type2) {
	return add2DTexture(image.bits(),image.width(),image.height(), type, type2);
}
TextureInfo * Renderer::add2DTexture(const char * fileName, bool flipHorz, bool flipVert) {
	QString data(fileName);
	return add2DTexture(data,flipHorz,flipVert);
}
TextureInfo * Renderer::add2DTexture(QString& fileName, bool flipHorz, bool flipVert) {
	QString filePath = /**/QCoreApplication::applicationDirPath() + /**/fileName;
	QFile tempFile(filePath);
	if(tempFile.exists()) {
		QImage data = getImageFromFile(filePath,flipHorz,flipVert);
		return add2DTexture(data);
	} else {
		qDebug() << "Invalid file path " << formatFileName(filePath) << " Texture not loaded";
		assert(false);
		return nullptr;
	}
}
TextureInfo * Renderer::add2DTexture(ubyte * data, uint width, uint height, GLenum fileType) {
	return add2DTexture(data,width,height,fileType,fileType);
}
TextureInfo * Renderer::add2DTexture(ubyte * data, uint width, uint height, GLenum fileType, GLenum fileType2) {
	static uint ID = 0;
	textures.add(TextureInfo());
	TextureInfo * ret = &textures.last();
	ret->slotID = ID++;
	glGenTextures(1,&ret->bufferID);
	update2DTexture(ret->bufferID,ret->slotID,data,width,height,fileType,fileType2);
	return ret;
}

TextureInfo * Renderer::addCubeTexture(QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ) {
	QString paths[] = { posX, negX, posY, negY, posZ, negZ };
	const int pathSize = sizeof(paths) / sizeof(*paths);
	QImage imageData[pathSize];
	ImageData ret[pathSize];

	for(int i=0;i<pathSize;i++) {
		QString filePath = /**/QCoreApplication::applicationDirPath() + /**/paths[i];
		QFile tempFile(filePath);
		if(tempFile.exists()) {
			imageData[i] = getImageFromFile(filePath,false,true);
			ret[i].init(imageData[i]);
		} else {
			qDebug() << "Invalid file path " << formatFileName(filePath) << " Texture not loaded";
			assert(false);
		}
	}
	return addCubeTexture(ret[0],ret[1],ret[2],ret[3],ret[4],ret[5]);
}
TextureInfo * Renderer::addCubeTexture(QString& directory,QString& posX,QString& negX,QString& posY,QString& negY,QString& posZ,QString& negZ) {
	QString paths[] = { posX, negX, posY, negY, posZ, negZ };
	const int pathSize = sizeof(paths) / sizeof(*paths);
	for(int i=0;i<pathSize;i++) {
		paths[i] = directory+"/"+paths[i];
	}
	return addCubeTexture(paths[0],paths[1],paths[2],paths[3],paths[4],paths[5]);
}
TextureInfo * Renderer::addCubeTexture(ImageData& posX,ImageData& negX,ImageData& posY,ImageData& negY,ImageData& posZ,ImageData& negZ) {
	static uint ID = 0;
	textures.add(TextureInfo());
	TextureInfo * ret = &textures.last();

	ret->slotID= ID++;

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1,&ret->bufferID);
	glActiveTexture(GL_TEXTURE0+ret->slotID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ret->bufferID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ImageData images[] = { posX, negX, posY, negY, posZ, negZ };
	const int pathSize = sizeof(images) / sizeof(*images);
	for(int i=0;i<pathSize;i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, images[i].type, images[i].width, images[i].height, 0, images[i].type, GL_UNSIGNED_BYTE, images[i].data);
	}

	return ret;
}
TextureInfo * Renderer::addCubeTexture(QImage& posX,QImage& negX,QImage& posY,QImage& negY,QImage& posZ,QImage& negZ) {
	ImageData data[] = { ImageData(posX),ImageData(negX),ImageData(posY),ImageData(negY),ImageData(posZ),ImageData(negZ) };
	return addCubeTexture(data[0],data[1],data[2],data[3],data[4],data[5]);
}

void            Renderer::draw(Renderable& toDraw) {
	if(toDraw.visible) {
		toDraw.transformData.lateUpdate();
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

void Renderer::draw(GeometryInfo * toDraw)
{
	draw(*toDraw);
}

void Renderer::draw(Renderable * toDraw)
{
	draw(*toDraw);
}

void            Renderer::drawPrep(int width, int height) {
	glClearColor(.1f,.1f,.1f,1);
	glViewport(0,0,width,height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}