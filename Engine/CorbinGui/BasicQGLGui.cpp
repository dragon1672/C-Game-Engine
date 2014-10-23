#include <gl/glew.h>
#include "BasicQGLGui.h"




void BasicQGLGui::initializeGL()
{
	meGame.initGl();
	meGame.start();
	connect(&timer,&QTimer::timeout,[this](){ this->update(); });
}
