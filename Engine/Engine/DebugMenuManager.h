#pragma once

#include <glm\glm.hpp>
#include <QtGui\QHBoxLayout>
#include <QtGui\QVBoxLayout>
#include <QtGui\qgridlayout.h>
#include <QtGui\qwidget.h>
#include "ExportHeader.h"

#include "WatchFloatController.h"
#include "SlideFloatController.h"
#include "BoolToggleController.h"
#include "WatchVectorController.h"
#include "SlideVectorController.h"
#include "ButtonInfo.h"
#include <vector>

class ENGINE_SHARED DebugMenuManager : public QWidget {
	QHBoxLayout * mainLayout;
	std::vector<DebugMenuControllers::WatchFloatController  *> floatWatchers;	QVBoxLayout * floatWatchCol;
	std::vector<DebugMenuControllers::SlideFloatController  *> floatSliders;	QVBoxLayout * floatSlideCol;
	std::vector<DebugMenuControllers::BoolToggleController  *> bools;			QVBoxLayout * boolCol;
	std::vector<DebugMenuControllers::WatchVectorController *> vecWatchers;		QVBoxLayout * vecWatchCol;
	std::vector<DebugMenuControllers::SlideVectorController *> vecSliders;		QVBoxLayout * vecSlideCol;
	std::vector<ButtonInfo *> buttons;											QVBoxLayout * buttonCol;
public:
	void init();
	void update();
	void watch(char * name, float& toWatch);							// float
	void watch(char * name, glm::vec3& toWatch);						// vector
	void edit (char * name, float& toWatch, float min, float max, bool doubleLink = true);		// float
	
	// vector
	void edit (char * name, glm::vec3& toWatch, float min, float max, bool doubleLink = true);
	void edit (char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink = true);
	void edit (char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink = true);
	
	void edit (char * name, bool& toWatch);								// bool
	void edit (char * name, fastdelegate::FastDelegate0<> callback);	// button
	void watchFloat (char * name, float& toWatch);
	void slideFloat (char * name, float& toWatch, float min, float max, bool doubleLink = true);
	void toggleBool (char * name, bool& toWatch);
	void watchVector(char * name, glm::vec3& toWatch);
	void slideVector(char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink = true);
	void slideVector(char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink = true);
	void slideVector(char * name, glm::vec3& toWatch, float min, float max, bool doubleLink = true);
	void button(char * name, fastdelegate::FastDelegate0<> callback);
};