#pragma once

#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenu.h>
#include <QtWidgets/QMenuBar>
#include <ExportHeader.h>
#include <QtWidgets/QTreeWidget>

#include <Engine/Tools/Printer.h>
#include <CorbinGui/BasicQGLGui.h>
#include <CorbinGui/Dependents/ComponentEditor.h>
#include <CorbinGui/Dependents/GameObjectViewer.h>
#include <CorbinGui/ToolWindowManager/ToolWindowManager.h>
#include <CorbinGui/ToolWindowManager/ToolWindowManagerArea.h>
#include <Engine/IO/Stream.h>

class ENGINE_SHARED GuiSkellyTon : public QMainWindow  {
	QTimer myTimer;
	BasicQGLGui * scene;
	QVBoxLayout * layout;
	GameObjectViewer *gameObjectList;
	EditorGame * game;
	
	ToolWindowManager * toolManager;
	ComponentEditor * componentEditor;
	QMenu * addComponentBar;
	QAction* StartStopGameAction;
	QAction* PlayResumeGameAction;
	QMenu * ResouceBar;
	QMenu * GameObjectMenu;

	enum EditorStates{
		Editor,PlayingGame,PlayingPaused//saving?
	} myState;
	Stream tempStreamForGamePlay;

	void LoadFromFile(Stream& s, bool backup = true, bool resources = false);
	void SaveToStream(Stream& s, bool resources = false);
	Stream ExportToStream(bool resources = false);
	void Disable();
	void Enable();
public:
	EditorGame * Game() const { return game; }
	GuiSkellyTon();

	void initBar();

	void ToggleGameStartStop();
	void ToggleGamePauseResume();

	void init();
	void update();
};