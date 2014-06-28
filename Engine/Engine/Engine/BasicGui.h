#pragma once


};
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


class BasicGui : public QMainWindow {
	//have debug section
	//have renderer
	//have virtual init/new frame
private:
	static const int TIDLE_KEY = 192;

	Q_OBJECT;

	SingleKeyManager toggleDebugMenu;

	WidgetRenderer meScene;
	DebugMenuManager * myDebugMenu;
	QTimer myTimer;

protected:
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
public:
	BasicGui()
	: toggleDebugMenu(TIDLE_KEY)
	{
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(myUpdate()));
		myTimer.start(0);


		//setup layout
		QVBoxLayout *layout = new QVBoxLayout;
		//setup mainwidget
		QWidget * window = new QWidget();
        window->setLayout(layout);

		//set up locals
		myDebugMenu = new DebugMenuManager();
		myDebugMenu->init();

		meScene.setMinimumHeight(700);
		meScene.setMinimumWidth(1200);
		meScene.init();

		//add local widgets
		layout->addWidget(myDebugMenu);
		layout->addWidget(&meScene);
		fileMenu = menuBar()->addMenu("File");

        // Set QWidget as the central layout of the main window
        setCentralWidget(window);
	}
private slots:
	void myUpdate();
protected:
	void nextFrame();

};