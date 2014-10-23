#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenu.h>
#include <QtWidgets/QMenuBar>
#include <ExportHeader.h>
#include <QtWidgets/QTreeWidget>

#include <Engine/Tools/Printer.h>
#include <CorbinGui/BasicQGLGui.h>

class ENGINE_SHARED GuiSkellyTon : public QMainWindow  {
	QMenu * fileMenu;
	QTimer myTimer;
	BasicQGLGui * scene;
	QVBoxLayout * layout;
public:
	GuiSkellyTon()
		: scene(new BasicQGLGui())
	{
		scene->setMinimumSize(500,500);
		connect(&myTimer,&QTimer::timeout,[this](){ this->update(); });

		layout = new QVBoxLayout;
		//setup mainwidget
		QWidget * window = new QWidget();
		window->setLayout(layout);
		layout->addWidget(scene);
		setCentralWidget(window);

		fileMenu = menuBar()->addMenu("File");
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
		fileMenu->addAction(action = new QAction("Load Obj", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Obj Clicked"); });
		fileMenu->addAction(action = new QAction("Load Texture", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Texture Clicked"); });
		fileMenu->addAction(action = new QAction("Load Shader", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Shader Clicked"); });
		fileMenu->addAction(action = new QAction("Load Script", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Load Script Clicked"); });
		fileMenu = menuBar()->addMenu("GameObject");
		fileMenu->addAction(action = new QAction("New Game Object", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("New Game Object Clicked"); });
		fileMenu = fileMenu->addMenu("Add Component");
		fileMenu->addAction(action = new QAction("Renderable Component", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Add Renderable Clicked"); });
		fileMenu->addAction(action = new QAction("collider Component", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Add collider Clicked"); });
		fileMenu->addAction(action = new QAction("Script Component", this));	connect(action, &QAction::triggered, [this](){ printer.LogMessage("Add Script Clicked"); });



		QTreeWidget *treeWidget = new QTreeWidget();
		treeWidget->setColumnCount(1);
		QList<QTreeWidgetItem *> items;
		for (int i = 0; i < 5; ++i) {
			QTreeWidgetItem *treeWidget2 = new QTreeWidgetItem((QTreeWidget*)0,QStringList(QString("item: %1").arg(i)));
			QList<QTreeWidgetItem *> items2;
			for (int i = 0; i < 5; ++i) {
				items2.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
			}
			treeWidget2->addChildren(items2);
			items.append(treeWidget2);
		}
		treeWidget->insertTopLevelItems(0, items);

		layout->addWidget(treeWidget);
	}

	Entity * addEntity(const char * name) {
		return scene->meGame.AddEntity(name);
	}

	void init() {
		scene->init();
		scene->startGameLoop();
	}
	void update() {
		scene->update();
	}
};