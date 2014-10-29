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

class ENGINE_SHARED GuiSkellyTon : public QMainWindow  {
	QTimer myTimer;
	BasicQGLGui * scene;
	QVBoxLayout * layout;
	GameObjectViewer *gameObjectList;
	EditorGame * game;
	ToolWindowManager * toolManager;
	ComponentEditor * componentEditor;
public:
	EditorGame * Game() const { return game; }
	GuiSkellyTon()
		: scene(new BasicQGLGui())
	{
		toolManager = new ToolWindowManager();
		componentEditor = new ComponentEditor();
		game = &scene->meGame;
		setCentralWidget(toolManager);
		gameObjectList = new GameObjectViewer(game);

		scene->setMinimumSize(500,500);
		connect(&myTimer,&QTimer::timeout,[this](){ this->update(); });

		scene->setWindowTitle("Game");

		toolManager->addToolWindow(scene,ToolWindowManager::AreaReferenceType::EmptySpace);

		
		initBar();


		connect(gameObjectList,&QTreeWidget::currentItemChanged,[this](QTreeWidgetItem *current, QTreeWidgetItem *previous){
			Entity * ECurrent  = GameObjectViewer::convertTree2Entity(current);
			Entity * EPrevious = GameObjectViewer::convertTree2Entity(previous);
			game->currentEntity.SetCurrent(ECurrent);

			std::string name1 = ECurrent  != nullptr ? std::string(ECurrent->Name())  : "NULL";
			std::string name2 = EPrevious != nullptr ? std::string(EPrevious->Name()) : "NULL";
			printer.LogMessage("from "+name2+" to "+name1);

			componentEditor->changeEntity(ECurrent,game->IsGameObject());

			this->update();
		});

		gameObjectList->setColumnCount(1);
		toolManager->addToolWindow(gameObjectList,ToolWindowManager::AreaReferenceType::EmptySpace);
		toolManager->addToolWindow(componentEditor,ToolWindowManager::AreaReferenceType::EmptySpace);
	}

	void initBar() {
		QMenu * fileMenu = menuBar()->addMenu("File");
		//setting up file actions
		QAction* action;
		fileMenu->addAction(action = new QAction("New Project", this));
		//action->setShortcut(QKeySequence::New);
		connect(action, &QAction::triggered, [this](){ printer.LogMessage("New Clicked"); });

		fileMenu->addAction(action = new QAction("Load Project", this));
		//action->setShortcut(QKeySequence::Open);
		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Open Clicked"); });

		fileMenu->addAction(action = new QAction("Save Project", this));
		//action->setShortcuts(QKeySequence::Save);
		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Save Clicked"); });

		fileMenu->addAction(action = new QAction("Exit Program", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Exit Clicked"); });

		fileMenu = menuBar()->addMenu("Resources");
		fileMenu->addAction(action = new QAction("Load Obj", this));		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Obj Clicked"); });
		fileMenu->addAction(action = new QAction("Load Texture", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Texture Clicked"); });
		fileMenu->addAction(action = new QAction("Load Shader", this));		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Shader Clicked"); });
		fileMenu->addAction(action = new QAction("Load Script", this));		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Script Clicked"); });
		fileMenu = menuBar()->addMenu("GameObject");
		fileMenu->addAction(action = new QAction("New Game Object", this));	connect(action, &QAction::triggered, [this](){ game->AddEntity("New Game Object"); });
		fileMenu = fileMenu->addMenu("Add Component");
		fileMenu->addAction(action = new QAction("Renderable Component", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Add Renderable Clicked"); });
		//fileMenu->addAction(action = new QAction("Collider Component", this));		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Add Collider Clicked"); });
		fileMenu->addAction(action = new QAction("Script Component", this));		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Add Script Clicked"); });
	}

	void init() {
		scene->init();
		scene->startGameLoop();
		scene->startup();
	}
	void update() {
		componentEditor->update();
	}
};