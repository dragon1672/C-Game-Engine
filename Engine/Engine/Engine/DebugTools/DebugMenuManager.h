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

#include <Engine\Tools\QT\ButtonInfo.h>
#include <Engine/FastDelegate.h>
#include <vector>

namespace DebugMenuControllers {
	class Controller {
	public:
		virtual void update() = 0;
	};
}

class ENGINE_SHARED DebugMenuManager {
	struct TabData {
		const char * name;
		QVBoxLayout * layout;
		int index;
	};
	std::vector<TabData> tabs;
	QTabWidget * tabManager;

	std::vector<DebugMenuControllers::Controller *> floatWatchers;
	std::vector<DebugMenuControllers::Controller *> floatSliders;
	std::vector<DebugMenuControllers::Controller *> bools;
	std::vector<DebugMenuControllers::Controller *> vecWatchers;
	std::vector<DebugMenuControllers::Controller *> vecSliders;
	std::vector<DebugMenuControllers::Controller *> nameSliders;
	std::vector<ButtonInfo *> buttons;

	QVBoxLayout * getTabLayout(const char * name);
	const char * defaultTabName; // default
public:
	//mainly used by GUI
	DebugMenuManager();
	void init() {} // included for backwards compatability
	void update();
	void hide();
	void show();
	bool isHidden();
	QWidget * getWidg();


	//returns current active tab
	//returns null if non found
	const char * getActiveTab();

	//returns true if tab is active
	bool isActiveTab(const char * tabname);

	//returns false if tab not found
	bool setActiveTab(const char * tabname);

	//if tab is not defined the default tab will be used
	void setDefaultTab(const char * tabname);
	//       ---------------------------------------- easy cover all function calls ----------------------------------------        //
	void watch(char * name, const char *& valueToWatch, char * tabName=nullptr);
	//floats
	void watch(char * name, float& toWatch, const char * tabName=nullptr);
	void edit (char * name, float& toWatch, float min, float max, bool doubleLink = true, const char * tabName=nullptr);
	//vectors
	void watch(char * name, glm::vec3& toWatch, const char * tabName=nullptr);
	void edit (char * name, glm::vec3& toWatch, float min, float max, bool doubleLink = true, const char * tabName=nullptr);
	void edit (char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink = true, const char * tabName=nullptr);
	void edit (char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink = true, const char * tabName=nullptr);
	void edit (char * name, bool& toWatch, const char * tabName=nullptr);								// bool
	void edit (char * name, fastdelegate::FastDelegate0<> callback, const char * tabName=nullptr);	// button

	//       ---------------------------------------- explicit function calls ----------------------------------------        //
	//       -------------------------------------- (Same effect as above calls) -------------------------------------        //
	void watchName(char * name, const char *& valueToWatch, char * tabName=nullptr);
	void watchFloat (char * name, float& toWatch, const char * tabName=nullptr);
	void slideFloat (char * name, float& toWatch, float min, float max, bool doubleLink = true, const char * tabName=nullptr);
	void toggleBool (char * name, bool& toWatch, const char * tabName=nullptr);
	void watchVector(char * name, glm::vec3& toWatch, const char * tabName=nullptr);
	void slideVector(char * name, glm::vec3& toWatch, float xRange, float yRange, float zRange, bool doubleLink = true, const char * tabName=nullptr);
	void slideVector(char * name, glm::vec3& toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink = true, const char * tabName=nullptr);
	void slideVector(char * name, glm::vec3& toWatch, float min, float max, bool doubleLink = true, const char * tabName=nullptr);
	void button(char * name, fastdelegate::FastDelegate0<> callback, const char * tabName=nullptr);
};