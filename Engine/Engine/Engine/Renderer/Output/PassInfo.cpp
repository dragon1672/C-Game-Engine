#include <GL\glew.h>
#include "PassInfo.h"
#include <Engine\Renderer\Shader\ShaderProgram.h>
#include <Qt/qdebug.h>

void PassInfo::initTextures(int width, int height) {
	glGenFramebuffers(1,&frameBufferID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER,frameBufferID);
	uint getColorTexture = ShaderProgram::load2DTexture(0,width,height,GL_RGBA);
	uint getDepthTexture = ShaderProgram::load2DTexture(0,width,height,GL_DEPTH_COMPONENT32);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, getColorTexture,0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, getDepthTexture,0);
	uint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE) { // returning error code: 36054, incomplete frame
		static int power = 0;

		qDebug() << "THE BUFFER (" << status << ") - ----- - - - - - - - - - - - - - - - --- -- - - - -  - -- -- -";
	}
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