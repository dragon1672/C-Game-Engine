#include "DebugMenuManager.h"

#ifdef _DEBUG

void DebugMenuManager::init() {
	mainLayout = new QHBoxLayout();
	floatWatchCol = new QVBoxLayout();
	floatSlideCol = new QVBoxLayout();
	boolCol = new QVBoxLayout();
	vecWatchCol = new QVBoxLayout();
	vecSlideCol = new QVBoxLayout();
	buttonCol = new QVBoxLayout();

	setLayout(mainLayout);
	mainLayout->addLayout(buttonCol);
	mainLayout->addLayout(boolCol);
	mainLayout->addLayout(floatWatchCol);
	mainLayout->addLayout(floatSlideCol);
	mainLayout->addLayout(vecWatchCol);
	mainLayout->addLayout(vecSlideCol);
}
void DebugMenuManager::update() {
	for (unsigned int i = 0; i < floatWatchers.size(); i++) { floatWatchers[i]->update();          }
	for (unsigned int i = 0; i < floatSliders.size();  i++) { floatSliders[i]->updateGUItoModel(); }
	for (unsigned int i = 0; i < bools.size();         i++) { bools[i]->updateGUItoModel();        }
	for (unsigned int i = 0; i < vecWatchers.size();   i++) { vecWatchers[i]->update();            }
	for (unsigned int i = 0; i < vecSliders.size();    i++) { vecSliders[i]->updateGUItoModel();   }
}
void DebugMenuManager::watchFloat (char * name, float& toWatch)	  {
	DebugMenuControllers::WatchFloatController * toAdd = new DebugMenuControllers::WatchFloatController();
	toAdd->init(name,&toWatch);
	floatWatchers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	floatWatchCol->addLayout(newRow);
}
void DebugMenuManager::slideFloat (char * name, float& toWatch, float min, float max)	  {
	DebugMenuControllers::SlideFloatController * toAdd = new DebugMenuControllers::SlideFloatController();
	toAdd->init(name,&toWatch,min,max);
	floatSliders.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	newRow->addWidget((toAdd->slider));
	floatSlideCol->addLayout(newRow);
}
void DebugMenuManager::toggleBool (char * name, bool& toWatch)	  {
	DebugMenuControllers::BoolToggleController * toAdd = new DebugMenuControllers::BoolToggleController();
	toAdd->init(name,&toWatch);
	bools.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->checkBox));
	boolCol->addLayout(newRow);
}
void DebugMenuManager::watchVector(char * name, glm::vec3& toWatch) {
	DebugMenuControllers::WatchVectorController * toAdd = new DebugMenuControllers::WatchVectorController();
	toAdd->init(name,&toWatch);
	vecWatchers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	vecWatchCol->addLayout(newRow);
}
void DebugMenuManager::slideVector(char * name, glm::vec3& toWatch, float min, float max) {
	DebugMenuControllers::SlideVectorController * toAdd = new DebugMenuControllers::SlideVectorController();
	toAdd->init(name,&toWatch,min,max);
	vecSliders.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->label);
	newRow->addWidget(toAdd->xSlider);
	newRow->addWidget(toAdd->ySlider);
	newRow->addWidget(toAdd->zSlider);
	vecSlideCol->addLayout(newRow);
}
void DebugMenuManager::button(char * name, fastdelegate::FastDelegate0<> callback) {
	auto * toAdd = new ButtonInfo();
	toAdd->init(name,callback);
	buttons.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->button);
	buttonCol->addLayout(newRow);
}

#endif