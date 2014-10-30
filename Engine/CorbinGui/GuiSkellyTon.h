#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenu.h>
#include <QtWidgets/QMenuBar>
#include <ExportHeader.h>
#include <QtWidgets/QTreeWidget>
#include <CorbinGui/GamePlayWindow.h>

#include <Engine/Tools/Printer.h>
#include <CorbinGui/BasicQGLGui.h>
#include <CorbinGui/Dependents/ComponentEditor.h>
#include <CorbinGui/Dependents/GameObjectViewer.h>
#include <CorbinGui/ToolWindowManager/ToolWindowManager.h>
#include <CorbinGui/ToolWindowManager/ToolWindowManagerArea.h>

class ENGINE_SHARED GuiSkellyTon : public QMainWindow  {
	QTimer myTimer;
	BasicQGLGui * scene;
	QVBoxLayout * layout;
	GameObjectViewer *gameObjectList;
	EditorGame * game;
	ToolWindowManager * toolManager;
	ComponentEditor * componentEditor;
	GamePlayWindow * gamePlayWindow;
	QMenu * addComponentBar;
public:
	EditorGame * Game() const { return game; }
	GuiSkellyTon();

	void initBar();

	void startGame() {
		//disable all editor components
		//remove selector function
		//start game loop
	}
	void stopGame() {
		//stop game loop
		//enable all editor components
		//add selector function
	}

	void init();
	void update();
};