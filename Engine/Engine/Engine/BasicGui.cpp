#include <Engine\BasicGui.h>

BasicGui::BasicGui(bool debugStartsVisable)
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
void BasicGui::addScene(WidgetRenderer * scene) {
	this->scene = scene;
	scene->setDebugMenu(myDebugMenu);
	layout->addWidget(scene);
	scene->setMinimumHeight(700);
	scene->setMinimumWidth(1200);
}
void BasicGui::mouseMoveEvent(QMouseEvent* e) { if(scene != nullptr) scene->mouseMoveEvent(e); }
void BasicGui::keyPressEvent(QKeyEvent* e) { if(scene != nullptr) scene->keyPressEvent(e); }
void BasicGui::privateUpdate() {
	toggleDebugMenu.update(.1f);
	if(toggleDebugMenu.hasBeenClicked()) {
		(myDebugMenu->isHidden()) ? myDebugMenu->show() : myDebugMenu->hide();
	}
	if(!myDebugMenu->isHidden()) myDebugMenu->update();
	update();
}