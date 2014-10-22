#pragma once

#include <QtOpenGL/QGLWidget>
#include <Engine/Systems/GameObjectManager.h>
#include <QtCore/QTimer>
#include <ExportHeader.h>
#include <Engine/Entity/Entity.h>


class ENGINE_SHARED BasicGui : public QGLWidget {
private:
	Q_OBJECT;
public: GameObjectManager meGame;
	QTimer timer;
public:
	void init() {
		meGame.init();
	}

	void initializeGL();

	void startGameLoop() {
		timer.start();
	}

	void update() {
		meGame.update();
		repaint();
	}

	void resizeGL(int w, int h)
	{
		glViewport(0, 0, w, h);
		meGame.width = w;
		meGame.height = h;
	}

	void paintGL()
	{
		meGame.paint();
	}

};