#include <gl/glew.h>
#include "BasicQGLGui.h"




void BasicQGLGui::initializeGL()
{
	meGame.initGl();
	junkTimer.setInterval(1000);
	connect(&timer,&QTimer::timeout,[this](){ this->update(); });
	connect(&junkTimer,&QTimer::timeout,[](){ LUA_INSTANCE.CollectGarbage(); });
	
}
