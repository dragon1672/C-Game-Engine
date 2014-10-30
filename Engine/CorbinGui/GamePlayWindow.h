#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include <Engine/Systems/GameObjectManager.h>

class GamePlayWindow : public QWidget {
	QTimer timer;
	GameObjectManager * game;
public:
	GamePlayWindow(GameObjectManager * game);
	void start();
	void stop();
	void paint();
};