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
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>

/*
	Don't forget to call add scene
//*/
class ENGINE_SHARED BasicGui : public QMainWindow {
private:
	static const int TIDLE_KEY = 192;

	Q_OBJECT;

	QTimer myTimer;

	QVBoxLayout * layout;
	WidgetRenderer * scene;

protected:
	DebugMenuManager * myDebugMenu;
	SingleKeyManager toggleDebugMenu;
	float dt;
public:
	BasicGui(bool debugStartsVisable = true)
	: toggleDebugMenu(TIDLE_KEY)
	{
		connect(&myTimer,SIGNAL(timeout()),this,SLOT(privateUpdate()));
		myTimer.start(0);

		//setup layout
		layout = new QVBoxLayout;
		QWidget * window = new QWidget();
        window->setLayout(layout);

		//set up locals
		myDebugMenu = new DebugMenuManager();
		myDebugMenu->init();

		if(!debugStartsVisable) myDebugMenu->hide();

		//add local widgets
		layout->addWidget(myDebugMenu);

		// Set QWidget as the central layout of the main window
        setCentralWidget(window);
	}
	void addScene(WidgetRenderer * scene) {
		this->scene = scene;
		layout->addWidget(scene);
		scene->setMinimumHeight(700);
		scene->setMinimumWidth(1200);
	}
	void mouseMoveEvent(QMouseEvent* e) { if(scene != nullptr) scene->mouseMoveEvent(e); }
	void keyPressEvent(QKeyEvent* e) { if(scene != nullptr) scene->keyPressEvent(e); }
private slots:
	void privateUpdate() {
		toggleDebugMenu.update(.1f);
		if(toggleDebugMenu.hasBeenClicked()) {
			(myDebugMenu->isHidden()) ? myDebugMenu->show() : myDebugMenu->hide();
		}
		if(!myDebugMenu->isHidden()) myDebugMenu->update();
		update();
	}
protected: // included for anyone wanting to expand on this basic GUI
	virtual void update() {}
};