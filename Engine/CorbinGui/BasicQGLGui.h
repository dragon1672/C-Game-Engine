#pragma once

#include <QtOpenGL/QGLWidget>
#include <Engine/Systems/GameObjectManager.h>
#include <QtCore/QTimer>
#include <ExportHeader.h>
#include <Engine/Entity/Entity.h>
#include <CorbinGui/EditorGame.h>


class ENGINE_SHARED BasicQGLGui : public QGLWidget {
private:
	Q_OBJECT;
	QTimer timer;
public:
	EditorGame meGame;
	BasicQGLGui();
	void init();

	void initializeGL();

	void startup();

	void startGameLoop();
	void stopGameLoop();

	void update();

	void resizeGL(int w, int h);

	void paintGL();

};