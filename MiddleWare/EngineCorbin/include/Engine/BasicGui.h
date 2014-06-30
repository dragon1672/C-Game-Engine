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
	BasicGui(bool debugStartsVisable = true);
	void addScene(WidgetRenderer * scene);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
private slots:
	void privateUpdate();
protected: // included for anyone wanting to expand on this basic GUI
	virtual void update() {}
};