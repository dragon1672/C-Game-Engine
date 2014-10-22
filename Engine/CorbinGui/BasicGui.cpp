#include <gl/glew.h>
#include "BasicGui.h"




void BasicGui::initializeGL()
{
	meGame.initGl();
	meGame.start();
	connect(&timer,&QTimer::timeout,[this](){ this->update(); });
}
