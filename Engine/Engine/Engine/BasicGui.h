#pragma once

#include <Qt\qtimer.h>

#include <QtGui\QHBoxLayout>
#include <QtGui\QVBoxLayout>
#include <QtGui\qgridlayout.h>
#include <QtGui\qwidget.h>
#include <Engine\DebugTools\DebugMenuManager.h>
#include <Engine\Tools\SingleKeyManager.h>
#include <Qt\qmainwindow.h>
#include <Engine\WidgetRenderer.h>
#include <Engine\Tools\Timer.h>
#include <ExportHeader.h>


class ENGINE_SHARED BasicGui : public QMainWindow {
	//have debug section
	//have renderer
	//have virtual init/new frame
private:
	static const int TIDLE_KEY = 192;

	Q_OBJECT;

	SingleKeyManager toggleDebugMenu;

	QTimer myTimer;
	Timer gameTimer;

protected:
	WidgetRenderer meScene;
	DebugMenuManager * myDebugMenu;
	float dt;
public:
	BasicGui()
	: toggleDebugMenu(TIDLE_KEY)
	{
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		myTimer.start(0);
		gameTimer.start();

		//setup layout
		QVBoxLayout * layout = new QVBoxLayout;
		//setup mainwidget
		QWidget * window = new QWidget();
        window->setLayout(layout);

		//set up locals
		myDebugMenu = new DebugMenuManager();
		myDebugMenu->init();

		meScene.setMinimumHeight(700);
		meScene.setMinimumWidth(1200);

		//add local widgets
		layout->addWidget(myDebugMenu);
		layout->addWidget(&meScene);

        // Set QWidget as the central layout of the main window
        setCentralWidget(window);
	}
private slots:
	void myUpdate() {
		
		dt = gameTimer.interval();
		
		nextFrame();

		meScene.repaint();
	}
protected:
	virtual void nextFrame() {}

};