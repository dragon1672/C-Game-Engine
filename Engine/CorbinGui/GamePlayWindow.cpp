#include "GamePlayWindow.h"
#include <QtWidgets/QVBoxLayout>

GamePlayWindow::GamePlayWindow(GameObjectManager * game) : game(game)
{
	setWindowTitle("Game");
	connect(&timer,&QTimer::timeout,[this](){
		this->game->update();
		this->repaint();
	});
}


void GamePlayWindow::start()
{
	this->game->start();
	timer.start();
}

void GamePlayWindow::stop()
{
	timer.stop();
}

void GamePlayWindow::paint()
{
	game->paint();
}
