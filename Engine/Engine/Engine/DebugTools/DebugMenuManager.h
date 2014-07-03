#pragma once

/*
	+--------------------------+
	|    Varables Explained    |
	+--------------------------+

	Double link : GUI updates model and model updates GUI
	[x,y,z]Range: will go from -Range -> Range
//*/

#include <glm\glm.hpp>
#include <QtGui\QHBoxLayout>
#include <QtGui\QVBoxLayout>
#include <QtGui\qgridlayout.h>
#include <QtGui\qwidget.h>
#include <ExportHeader.h>

#include <Qt/qtabwidget.h>

#include <Engine\DebugTools\MenuControllers\WatchFloatController.h>
#include <Engine\DebugTools\MenuControllers\SlideFloatController.h>
#include <Engine\DebugTools\MenuControllers\BoolToggleController.h>
#include <Engine\DebugTools\MenuControllers\WatchVectorController.h>
#include <Engine\DebugTools\MenuControllers\SlideVectorController.h>
#include <Engine\DebugTools\MenuControllers\CharPointerController.h>
#include <Engine\Tools\QT\ButtonInfo.h>
#include <Engine/FastDelegate.h>
#include <vector>

class ENGINE_SHARED DebugMenuManager : public QTabWidget {
	struct TabData {
		const char * name;
		QVBoxLayout * layout;
	};
	std::vector<TabData> tabs;

	std::vector<DebugMenuControllers::WatchFloatController  *> floatWatchers;
	std::vector<DebugMenuControllers::SlideFloatController  *> floatSliders;
	std::vector<DebugMenuControllers::BoolToggleController  *> bools;
	std::vector<DebugMenuControllers::WatchVectorController *> vecWatchers;
	std::vector<DebugMenuControllers::SlideVectorController *> vecSliders;
	std::vector<DebugMenuControllers::CharPointerController *> nameSliders;
	std::vector<ButtonInfo *> buttons;

	QVBoxLayout * getTabLayout(const char * name);
public:
	void init() {} // included for backwards compatability
	void update();
	//       ---------------------------------------- easy cover all function calls ----------------------------------------        //
	void watch(char * name, char *& valueToWatch, char * tabName="default");
	//floats
	void watch(char * name, float& toWatch, const char * tabName="default");
	void edit (char * name, float& toWatch, float min, float max, bool doubleLink = true, const char * tabName="default");
	//vectors
	void watch(char * name, glm::vec3& toWatch, const char * tabName="default");
	void edit (char * name, glm::vec3& toWatch, float min, float max, bool doubleLink = true, const char * tabName="default");
	void edit (char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink = true, const char * tabName="default");
	void edit (char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink = true, const char * tabName="default");
	void edit (char * name, bool& toWatch, const char * tabName="default");								// bool
	void edit (char * name, fastdelegate::FastDelegate0<> callback, const char * tabName="default");	// button

	//       ---------------------------------------- explicit function calls ----------------------------------------        //
	//       -------------------------------------- (Same effect as above calls) -------------------------------------        //
	void watchName(char * name, char *& valueToWatch, char * tabName="default");
	void watchFloat (char * name, float& toWatch, const char * tabName="default");
	void slideFloat (char * name, float& toWatch, float min, float max, bool doubleLink = true, const char * tabName="default");
	void toggleBool (char * name, bool& toWatch, const char * tabName="default");
	void watchVector(char * name, glm::vec3& toWatch, const char * tabName="default");
	void slideVector(char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink = true, const char * tabName="default");
	void slideVector(char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink = true, const char * tabName="default");
	void slideVector(char * name, glm::vec3& toWatch, float min, float max, bool doubleLink = true, const char * tabName="default");
	void button(char * name, fastdelegate::FastDelegate0<> callback, const char * tabName="default");
};