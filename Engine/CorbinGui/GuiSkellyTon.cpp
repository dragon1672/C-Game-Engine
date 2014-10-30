#include "GuiSkellyTon.h"
#include <Engine/Tools/Printer.h>



GuiSkellyTon::GuiSkellyTon() : scene(new BasicQGLGui())
{
	game = &scene->meGame;
	toolManager = new ToolWindowManager();
	componentEditor = new ComponentEditor();
	setCentralWidget(toolManager);
	gameObjectList = new GameObjectViewer(game);

	scene->setMinimumSize(500,500);
	connect(&myTimer,&QTimer::timeout,[this](){ this->update(); });

	scene->setWindowTitle("Editor");

	toolManager->addToolWindow(scene,ToolWindowManager::AreaReferenceType::EmptySpace);


	initBar();


	connect(gameObjectList,&QTreeWidget::currentItemChanged,[this](QTreeWidgetItem *current, QTreeWidgetItem *previous){
		Entity * ECurrent  = GameObjectViewer::convertTree2Entity(current);
		Entity * EPrevious = GameObjectViewer::convertTree2Entity(previous);
		game->currentEntity.SetCurrent(ECurrent);

		std::string name1 = ECurrent  != nullptr ? std::string(ECurrent->Name())  : "NULL";
		std::string name2 = EPrevious != nullptr ? std::string(EPrevious->Name()) : "NULL";
		printMsg(0) "from",name2,"to",name1;

		componentEditor->changeEntity(ECurrent,game->IsGameObject());

		addComponentBar->setEnabled(ECurrent != nullptr);

		this->update();
	});

	gameObjectList->setColumnCount(1);
	toolManager->addToolWindow(gameObjectList,ToolWindowManager::AreaReferenceType::EmptySpace);
	toolManager->addToolWindow(componentEditor,ToolWindowManager::AreaReferenceType::EmptySpace);
	myTimer.start();
}

void GuiSkellyTon::init()
{
	scene->init();
	scene->startGameLoop();
	scene->startup();
}

void GuiSkellyTon::update()
{
	componentEditor->update();
}

void GuiSkellyTon::initBar()
{
	QMenu * fileMenu = menuBar()->addMenu("File");
	//setting up file actions
	QAction* action; // master action, used to preserve context
	fileMenu->addAction(action = new QAction("New Project", this));		action->setShortcut(QKeySequence::New);
	connect(action, &QAction::triggered, [this](){ // TODO
		printer.LogMessage("New Clicked");
	});

	fileMenu->addAction(action = new QAction("Load Project", this));	action->setShortcut(QKeySequence::Open);
	connect(action, &QAction::triggered, [this](){ // TODO
		printer.LogMessage("Open Clicked");
	});

	fileMenu->addAction(action = new QAction("Save Project", this));	action->setShortcuts(QKeySequence::Save);
	connect(action, &QAction::triggered, [this](){ // TODO
		printer.LogMessage("Save Clicked");
	});

	fileMenu->addAction(action = new QAction("Exit Program", this));
	connect(action, &QAction::triggered, [this](){
		printer.LogMessage("Exiting Editor");
		this->close();
	});

	fileMenu = ResouceBar = menuBar()->addMenu("Resources");
	fileMenu->addAction(action = new QAction("Load Obj", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		printer.LogMessage("Load Obj Clicked");
	});
	fileMenu->addAction(action = new QAction("Load Texture", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		printer.LogMessage("Load Texture Clicked");
	});
	fileMenu->addAction(action = new QAction("Load Shader", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		printer.LogMessage("Load Shader Clicked");
	});
	fileMenu->addAction(action = new QAction("Load Script", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		printer.LogMessage("Load Script Clicked");
	});
	fileMenu = GameObjectMenu = menuBar()->addMenu("GameObject");
	fileMenu->addAction(action = new QAction("New Game Object", this));
	connect(action, &QAction::triggered, [this](){
		game->AddEntity("New Game Object");
	});


	//start/stop
	menuBar()->addAction(action = new QAction("Start Game", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		this->startGame();
	});
	StartGameAction = action;
	menuBar()->addAction(action = new QAction("Stop Game", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		this->stopGame();
	});
	StopGameAction = action;
	StopGameAction->setEnabled(false);


	addComponentBar = fileMenu->addMenu("Add Component");
	addComponentBar->addAction(action = new QAction("Renderable Component", this));
	connect(action, &QAction::triggered, [this](){
		this->game->currentEntity.addComponent<RenderableComponent>();
		componentEditor->changeEntity(this->game->currentEntity.GetCurrent(),game->IsGameObject());
	});
	//addComponentBar->addAction(action = new QAction("Collider Component", this));		connect(action, &QAction::triggered, [this](){ printer.LogMessage("Add Collider Clicked"); });
	addComponentBar->addAction(action = new QAction("Script Component", this));
	connect(action, &QAction::triggered, [this](){
		this->game->currentEntity.addComponent<ScriptComponent>();
		componentEditor->changeEntity(this->game->currentEntity.GetCurrent(),game->IsGameObject());
	});
}

void GuiSkellyTon::startGame()
{
	if(game->Game()->Valid()) {
		//disable all editor components
		//remove selector function
		game->Game()->init();
		game->Game()->SelectorFunction(game->IsGameObject());
		game->Game()->ComponentSelectorFunction(game->IsGameObject());
		
		game->Game()->saveValues();

		game->start();

		ResouceBar->setEnabled(false);
		GameObjectMenu->setEnabled(false);

		StartGameAction->setEnabled(false);
		StopGameAction->setEnabled(true);
	} else {
		printErr(100) "Not all components have been initialized";
	}
}

void GuiSkellyTon::stopGame()
{
	//stop game loop
	//enable all editor components
	//add selector function
	game->Game()->restoreValues();

	game->Game()->SelectorFunction(game->IsEditorObject());
	game->Game()->ComponentSelectorFunction(game->IsEditorObject());
	game->start();

	ResouceBar->setEnabled(true);
	GameObjectMenu->setEnabled(true);

	StartGameAction->setEnabled(true);
	StopGameAction->setEnabled(false);
}
