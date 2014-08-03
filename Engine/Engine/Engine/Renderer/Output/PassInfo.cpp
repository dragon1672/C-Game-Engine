#include <GL\glew.h>
#include "PassInfo.h"
#include <Engine\Renderer\Shader\ShaderProgram.h>
#include <Qt/qdebug.h>

void PassInfo::initTextures(int width, int height) {
	glGenFramebuffers(1,&frameBufferID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,frameBufferID);
	colorTexture = ShaderProgram::load2DTexture(0,width,height,GL_RGBA);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture+1,0);
	depthTexture = ShaderProgram::load2DTexture(0,width,height,GL_DEPTH_COMPONENT32,GL_DEPTH_COMPONENT);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture+1,0);
	uint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE) { // returning error code: 36054, incomplete frame
		qDebug() << "THE BUFFER (" << status << ") - ----- - - - - - - - - - - - - - - - --- --";
	}
}
void PassInfo::updateTextureSize(int width,int height) {
	//initTextures(width,height);
	//ShaderProgram::update2DTexture(colorTexture+1,colorTexture,0,width,height);
	//ShaderProgram::update2DTexture(depthTexture+1,depthTexture,0,width,height);
}
void PassInfo::activate() {
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}

//function pointer preDraw
bool PassInfo::contains(Renderable * toCheck) {
	for (int i = 0; i < myRenderables.size(); i++)
		if(myRenderables[i] == toCheck) return true;
	return false;
}
void PassInfo::add(Renderable * toAdd) {
	myRenderables.push_back(toAdd);
}
void PassInfo::remove(Renderable * toRemove) {
	for (int i = 0; i < myRenderables.size(); i++) {
		if(myRenderables[i] == toRemove) {
			myRenderables.erase(myRenderables.begin() + i);
			return; // we are done here
		}
	}
}
void PassInfo::loadRenderables(PassInfo * toLoadFrom, bool allowDups) {
	for (int i = 0; i < toLoadFrom->myRenderables.size(); i++)
	{
		if(allowDups || !contains(toLoadFrom->myRenderables[i]))
			myRenderables.push_back(toLoadFrom->myRenderables[i]);
	}
}