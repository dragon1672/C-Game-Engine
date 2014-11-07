#include "GuiSkellyTon.h"
#include <Engine/Tools/Printer.h>
#include <QtWidgets/QFileDialog>
#include <Engine/Systems/GameObjectManager.h>
#include <CorbinGui/Dependents/ResourceViewer.h>




GuiSkellyTon::GuiSkellyTon()
{
	myState = EditorStates::Editor;
	scene = new BasicQGLGui();
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

	toolManager->addToolWindow(gameObjectList, ToolWindowManager::AreaReferenceType::EmptySpace);
	toolManager->addToolWindow(componentEditor,ToolWindowManager::AreaReferenceType::EmptySpace);
	toolManager->addToolWindow(new ResourceViewer(), ToolWindowManager::AreaReferenceType::EmptySpace);
	myTimer.start();
}

void GuiSkellyTon::init()
{
	scene->init();
	scene->startGameLoop();
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
		QString workingDir = resourceManager.WorkingDir().c_str();
		QString targetObj = QFileDialog::getOpenFileName(this, "Open OBJ", workingDir, "Model Files (*.obj)");
		if(targetObj == "")
			return;

		QString command("CSharpOBJConverter.exe ");
		const char* nativeFileName = "level.bin";
		command += "\""+targetObj + "\"" + " " + "\"" + nativeFileName+ "\"";
		int result = system(command.toUtf8().constData());
		if(result!=0) {
			printErr(100) "File failed to load";
		} else {
			auto tmp = resourceManager.addMesh("From File",nativeFileName);
			tmp->PassDownToHardWare();
		}
		printer.LogMessage("Load Obj Clicked");
	});
	fileMenu->addAction(action = new QAction("Load Texture", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		QString workingDir = resourceManager.WorkingDir().c_str();
		QString targetObj = QFileDialog::getOpenFileName(this, "Open Texture", workingDir, "Supported Images (*.png)"); if(targetObj == "") return;

		auto tmp = resourceManager.add2DTexture("From File",targetObj.toStdString());
		tmp->PassDownToHardWare();
		printer.LogMessage("Load Texture Clicked");
	});
	fileMenu->addAction(action = new QAction("Load Shader", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		QString workingDir = resourceManager.WorkingDir().c_str();
		QString FragPath = QFileDialog::getOpenFileName(this, "Open FragShader",  workingDir, "Shader (*.glsl)");	if(FragPath == "") return;
		QString VertPath = QFileDialog::getOpenFileName(this, "Open VertexShader", workingDir, "Shader (*.glsl)");	if(VertPath == "") return;

		auto tmp = resourceManager.addShader_file("From File",VertPath.toStdString(),FragPath.toStdString());
		tmp->PassDownToHardWare();
		printer.LogMessage("Load Shader Clicked");
	});
	fileMenu->addAction(action = new QAction("Load Script", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		QString workingDir = resourceManager.WorkingDir().c_str();
		QString targetObj = QFileDialog::getOpenFileName(this, "Open Script", workingDir, "Supported Images (*.CorbinLua)"); if(targetObj == "") return;

		auto tmp = resourceManager.addScript_file(targetObj.toStdString());
		tmp->PassDownToHardWare();
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
		this->ToggleGameStartStop();
	});
	StartStopGameAction = action;
	menuBar()->addAction(action = new QAction("", this));
	connect(action, &QAction::triggered, [this](){ // TODO
		this->ToggleGamePauseResume();
	});
	PlayResumeGameAction = action;
	PlayResumeGameAction->setEnabled(false);


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

void GuiSkellyTon::ToggleGameStartStop()
{
	if(myState == EditorStates::Editor) { // start!
		if(gameManager.Valid()) {
			myState = EditorStates::PlayingGame;
			camManager.ActiveCam(nullptr);
			//disable all editor components
			//remove selector function
			gameManager.init();

			game->start();

			gameManager.ComponentSelectorFunction(game->IsGameObject());
		
			gameManager.saveValues();

			ResouceBar->setEnabled(false);
			GameObjectMenu->setEnabled(false);

			StartStopGameAction->setEnabled(true);
			StartStopGameAction->setText("Stop Game");
			PlayResumeGameAction->setEnabled(true);
			PlayResumeGameAction->setText("Pause");
		} else {
			auto tmp = gameManager.getErrors();
			for (uint i = 0; i < tmp.size(); i++)
			{
				printErr(100) tmp[0];
			}
		}
	} else if (myState == EditorStates::PlayingGame || EditorStates::PlayingPaused) { // stop the phone!
		myState = EditorStates::Editor;
		gameManager.restoreValues();

		gameManager.ComponentSelectorFunction(game->IsEditorObject());
		game->start();

		ResouceBar->setEnabled(true);
		GameObjectMenu->setEnabled(true);

		StartStopGameAction->setEnabled(true);
		StartStopGameAction->setText("Start Game");
		PlayResumeGameAction->setEnabled(false);
		PlayResumeGameAction->setText("");
	}
}

void GuiSkellyTon::ToggleGamePauseResume()
{
	if(myState == EditorStates::PlayingGame) { // hold the phone
		myState = EditorStates::PlayingPaused;
		gameManager.ComponentSelectorFunction([this](Object*o){
			if(std::string(typeid(RenderableComponent).name()).compare(typeid(*o).name()) == 0)
				return game->IsGameObject()(o);
			return false;
		});
		PlayResumeGameAction->setText("Resume");
	} else if(myState == EditorStates::PlayingPaused) { // time to resume
		myState = EditorStates::PlayingGame;
		gameManager.ComponentSelectorFunction(game->IsGameObject());
		PlayResumeGameAction->setText("Resume");
	}
}
