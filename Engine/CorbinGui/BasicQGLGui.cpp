#include <gl/glew.h>
#include "BasicQGLGui.h"




void BasicQGLGui::initializeGL()
{
	meGame.initGl();
	connect(&timer,&QTimer::timeout,[this](){ this->update(); });
	
}

void BasicQGLGui::init()
{
	meGame.init();
}

void BasicQGLGui::startup()
{
	meGame.start();
}

void BasicQGLGui::startGameLoop()
{
	timer.start();
}

void BasicQGLGui::stopGameLoop()
{
	timer.stop();
}

void BasicQGLGui::update()
{
	meGame.update();
	repaint();
}

void BasicQGLGui::resizeGL(int w, int h)
{
	//glViewport(0, 0, w, h);
	meGame.width = w;
	meGame.height = h;
}

void BasicQGLGui::paintGL()
{
	meGame.paint([this](int startX,int startY,int width,int height) {
		glViewport(startX,startY,width,height);
	});
}
