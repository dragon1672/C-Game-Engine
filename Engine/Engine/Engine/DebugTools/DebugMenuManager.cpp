#include "DebugMenuManager.h"
#include <Engine\unsigned.h>

QVBoxLayout * DebugMenuManager::getTabLayout(const char * name) {
	for (uint i = 0; i < tabs.size(); i++)
	{
		if(name == tabs[i].name) return tabs[i].layout;
	}
	QVBoxLayout * layout = new QVBoxLayout();
	QWidget * widg = new QWidget();
		
	widg -> setLayout(layout);
		
	addTab(widg,name);
	TabData toAdd = {name,layout};
	tabs.push_back( toAdd );
	return layout;
}

void DebugMenuManager::update() {
	for (uint i = 0; i < floatWatchers.size(); i++) { floatWatchers[i]->update();          }
	for (uint i = 0; i < floatSliders.size();  i++) { floatSliders[i]->updateGUItoModel(); }
	for (uint i = 0; i < bools.size();         i++) { bools[i]->updateGUItoModel();        }
	for (uint i = 0; i < vecWatchers.size();   i++) { vecWatchers[i]->update();            }
	for (uint i = 0; i < vecSliders.size();    i++) { vecSliders[i]->updateGUItoModel();   }
	for (uint i = 0; i < nameSliders.size();   i++) { nameSliders[i]->update();            }
}

void DebugMenuManager::watch(char * name, char *& valueToWatch, char * tabName) {
	watchName(name,valueToWatch,tabName);
}
void DebugMenuManager::watch(char * name, float& toWatch, const char * tabName) {
	watchFloat(name, toWatch,tabName);
}
void DebugMenuManager::watch(char * name, glm::vec3& toWatch, const char * tabName) {
	watchVector(name,toWatch,tabName);
}
void DebugMenuManager::edit (char * name, float& toWatch, float min, float max, bool doubleLink, const char * tabName) {
	slideFloat(name,toWatch,min,max,doubleLink,tabName);
}
void DebugMenuManager::edit (char * name, glm::vec3& toWatch, float min, float max, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,min,max,doubleLink,tabName);
}
void DebugMenuManager::edit (char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,xRange,yRange,zRange,doubleLink,tabName);
}
void DebugMenuManager::edit (char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,xMin,xMax,yMin,yMax,zMin,zMax,doubleLink,tabName);
}
void DebugMenuManager::edit (char * name, bool& toWatch, const char * tabName) {
	toggleBool(name,toWatch,tabName);
}
void DebugMenuManager::edit (char * name, fastdelegate::FastDelegate0<> callback, const char * tabName) {
	button(name,callback,tabName);
}
void DebugMenuManager::watchName(char * name, char *& valueToWatch, char * tabName) {
	auto * toAdd = new DebugMenuControllers::CharPointerController();
	toAdd->init(name,&valueToWatch);
	nameSliders.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->label);
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchFloat (char * name, float& toWatch, const char * tabName)	  {
	DebugMenuControllers::WatchFloatController * toAdd = new DebugMenuControllers::WatchFloatController();
	toAdd->init(name,&toWatch);
	floatWatchers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::slideFloat (char * name, float& toWatch, float min, float max, bool doubleLink, const char * tabName)	  {
	DebugMenuControllers::SlideFloatController * toAdd = new DebugMenuControllers::SlideFloatController();
	toAdd->init(name,&toWatch,min,max, doubleLink);
	floatSliders.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	newRow->addWidget((toAdd->slider));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::toggleBool (char * name, bool& toWatch, const char * tabName)	  {
	DebugMenuControllers::BoolToggleController * toAdd = new DebugMenuControllers::BoolToggleController();
	toAdd->init(name,&toWatch);
	bools.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->checkBox));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchVector(char * name, glm::vec3& toWatch, const char * tabName) {
	DebugMenuControllers::WatchVectorController * toAdd = new DebugMenuControllers::WatchVectorController();
	toAdd->init(name,&toWatch);
	vecWatchers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::slideVector(char * name, glm::vec3& toWatch, float min, float max, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,min,max,min,max,min,max,doubleLink,tabName);
}
void DebugMenuManager::slideVector(char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,-xRange,xRange,-yRange,yRange,-zRange,zRange,doubleLink,tabName);
}
void DebugMenuManager::slideVector(char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink, const char * tabName) {
	DebugMenuControllers::SlideVectorController * toAdd = new DebugMenuControllers::SlideVectorController();
	toAdd->init(name,&toWatch,xMin,xMax,yMin,yMax,zMin,zMax, doubleLink);
	vecSliders.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->label);
	newRow->addWidget(toAdd->xSlider);
	newRow->addWidget(toAdd->ySlider);
	newRow->addWidget(toAdd->zSlider);
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::button(char * name, fastdelegate::FastDelegate0<> callback, const char * tabName) {
	auto * toAdd = new ButtonInfo();
	toAdd->init(name,callback);
	buttons.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->button);
	getTabLayout(tabName)->addLayout(newRow);
}
