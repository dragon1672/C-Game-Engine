#include "DebugMenuManager.h"
#include <Engine\unsigned.h>

#include <Qt/qcheckbox.h>
#include <Qt/qlabel.h>
#include <Engine\Tools\QT\LinkedSlider.h>
#include <sstream>
#include <iomanip>
#include <Engine\Tools\QT\LinkedIntSlider.h>
#include <Qt/qtablewidget.h>


namespace DebugMenuControllers {
	class BoolToggleController : public Controller {
	public:
		QCheckBox * checkBox;
		bool * dataBound;

		BoolToggleController() {
			checkBox = new QCheckBox();
		}

		inline void init(const char * name, bool * toWatch) {
			checkBox->setText(name);
			dataBound = toWatch;
			updateModeltoGUI();
		}
		inline void updateGUItoModel() {
			*dataBound = checkBox->isChecked();
		}
		inline void updateModeltoGUI() {
			checkBox->setChecked(*dataBound);
		}
		inline void update() {
			updateGUItoModel();
		}
	};
	class CharPointerController : public Controller {
	public:
		QLabel * label;
		const char * title;
		const char ** data;

		CharPointerController() {
			label = new QLabel();
		}
		inline void init(const char * name, const char ** toWatch) {
			title = name;
			data = toWatch;
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << title << *data;
			label->setText(QString( ss.str().c_str() ));
		}
	};
	class SlideFloatController : public Controller {
	public:
		QLabel * label;
		float * data;
		LinkedSlider * slider;
		bool doubleLink;

		SlideFloatController() {
			label = new QLabel();
			slider = new LinkedSlider();
		}
		inline void init(const char * name, float * toWatch, float min, float max, bool doubleLink) {
			this->doubleLink = doubleLink;
			data = toWatch;
			label->setText(name);
			float floatData = *toWatch;
			slider->setBoundValue(toWatch);
			slider->setMin(min);
			slider->setMax(max);
			*toWatch = floatData;
			updateModeltoGUI();

		}
		inline void updateGUItoModel() {
			if(doubleLink) {
				updateModeltoGUI();
			}
		}
		inline void updateModeltoGUI() {
			slider->setBoundValue(data);
		}
		inline void update() { updateGUItoModel(); }
	};
	class SlideVectorController : public Controller {
	public:
		QLabel * label;
		LinkedSlider * xSlider;
		LinkedSlider * ySlider;
		LinkedSlider * zSlider;
		glm::vec3 * data;
		bool doubleLink;

		SlideVectorController() {
			label   = new QLabel();
			xSlider = new LinkedSlider();
			ySlider = new LinkedSlider();
			zSlider = new LinkedSlider();
		}

		inline void init(const char * name, glm::vec3 * toWatch, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax, bool doubleLink) {
			data = toWatch;
			this->doubleLink = doubleLink;
			label->setText(name);
			updateModeltoGUI();
			glm::vec3 tempSave = *toWatch;
			xSlider->setMin(xMin);	xSlider->setMinimumWidth(30);	xSlider->setMax(xMax);
			ySlider->setMin(yMin);	ySlider->setMinimumWidth(30);	ySlider->setMax(yMax);
			zSlider->setMin(zMin);	zSlider->setMinimumWidth(30);	zSlider->setMax(zMax);
			*toWatch = tempSave;
			updateModeltoGUI();
		}
		inline void updateGUItoModel() {
			if(doubleLink) {
				updateModeltoGUI();
			}
		}
		inline void updateModeltoGUI() {
			xSlider->setBoundValue(&data->x);
			ySlider->setBoundValue(&data->y);
			zSlider->setBoundValue(&data->z);
		}
		inline void update() { updateGUItoModel(); }
	};
	class WatchFloatController : public Controller {
	public:
		const char * title;
		float * data;
		QLabel * label;
		WatchFloatController() {
			label = new QLabel();
		}
		inline void init(const char * name, float * toWatch) {
			title = name;
			data = toWatch;
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << title << ": " << std::fixed << std::setprecision( 6 ) << *data;
			label->setText(QString( ss.str().c_str() ));
		}
	};
	class WatchVectorController : public Controller {
	public:
		const char * title;
		QLabel * label;
		glm::vec3 * data;

		WatchVectorController() {
			label = new QLabel() ;
		}

		inline void init(const char * name, glm::vec3 * toWatch) {
			title = name;
			data = toWatch;
			label->setText(name);
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << std::fixed << std::setprecision( 6 ) << title << ": {" << data->x << ", " << data->y << ", " << data->z << " }";
			label->setText(QString( ss.str().c_str() ));
		}
	};
	class WatchIntController : public Controller {
	public:
		const char * title;
		QLabel * label;
		int * data;

		WatchIntController() {
			label = new QLabel() ;
		}

		inline void init(const char * name, int * toWatch) {
			title = name;
			data = toWatch;
			label->setText(name);
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << std::fixed << title << ": " << *data;
			label->setText(QString( ss.str().c_str() ));
		}
	};
	class WatchVector4Controller : public Controller {
	public:
		const char * title;
		QLabel * label;
		glm::vec4 * data;

		WatchVector4Controller() {
			label = new QLabel() ;
		}

		inline void init(const char * name, glm::vec4 * toWatch) {
			title = name;
			data = toWatch;
			label->setText(name);
			update();
		}
		inline void update() {
			std::stringstream ss;
			ss << std::fixed << std::setprecision( 6 ) << title << ": {" << data->r << ", " << data->g << ", " << data->b << ", " << data->a << " }";
			label->setText(QString( ss.str().c_str() ));
		}
	};
	class SlideIntController : public Controller {
	public:
		QLabel * label;
		int * data;
		LinkedIntSlider * slider;
		bool doubleLink;

		SlideIntController() {
			label = new QLabel();
			slider = new LinkedIntSlider();
		}
		inline void init(const char * name, int * toWatch, int min, int max, bool doubleLink) {
			this->doubleLink = doubleLink;
			data = toWatch;
			label->setText(name);
			float floatData = *toWatch;
			slider->setBoundValue(toWatch);
			slider->setMin(min);
			slider->setMax(max);
			int range = abs(max - min);
			slider->setGranularity(range);
			*toWatch = floatData;
			updateModeltoGUI();

		}
		inline void updateGUItoModel() {
			if(doubleLink) {
				updateModeltoGUI();
			}
		}
		inline void updateModeltoGUI() {
			slider->setBoundValue(data);
		}
		inline void update() { updateGUItoModel(); }
	};
	class SlideVector4Controller : public Controller {
	public:
		QLabel * label;
		LinkedSlider * rSlider;
		LinkedSlider * gSlider;
		LinkedSlider * bSlider;
		LinkedSlider * aSlider;
		glm::vec4 * data;
		bool doubleLink;

		SlideVector4Controller() {
			label   = new QLabel();
			rSlider = new LinkedSlider();
			gSlider = new LinkedSlider();
			bSlider = new LinkedSlider();
			aSlider = new LinkedSlider();
		}

		inline void init(const char * name, glm::vec4 * toWatch, float rMin, float rMax, float gMin, float gMax, float bMin, float bMax, float aMin, float aMax, bool doubleLink) {
			data = toWatch;
			this->doubleLink = doubleLink;
			label->setText(name);
			updateModeltoGUI();
			glm::vec4 tempSave = *toWatch;
			rSlider->setMin(rMin);	rSlider->setMinimumWidth(30);	rSlider->setMax(rMax);
			gSlider->setMin(gMin);	gSlider->setMinimumWidth(30);	gSlider->setMax(gMax);
			bSlider->setMin(bMin);	bSlider->setMinimumWidth(30);	bSlider->setMax(bMax);
			aSlider->setMin(aMin);	aSlider->setMinimumWidth(30);	aSlider->setMax(aMax);
			*toWatch = tempSave;
			updateModeltoGUI();
		}
		inline void updateGUItoModel() {
			if(doubleLink) {
				updateModeltoGUI();
			}
		}
		inline void updateModeltoGUI() {
			rSlider->setBoundValue(&data->r);
			gSlider->setBoundValue(&data->g);
			bSlider->setBoundValue(&data->b);
			aSlider->setBoundValue(&data->a);
		}
		inline void update() { updateGUItoModel(); }
	};
	class WatchMat4Controller : public Controller {
	public:
		static const int size = 4;
		const char * title;
		QLabel * label;
		QTableWidget * table;
		glm::mat4 * data;

		WatchMat4Controller() {
			table = new QTableWidget(size,size) ;
			label = new QLabel();
			for(int i = 0; i < size; i++) {
				for(int j = 0; j < size; j++)
					table->setItem(i, j, new QTableWidgetItem(
									  QString("label %1")
									  .arg(i * size + j + 1)));
			}
		}

		inline void init(const char * name, glm::mat4 * toWatch) {
			title = name;
			data = toWatch;
			label->setText(name);
			update();
		}
		inline void update() {
			for(int i=0;i<size;i++) {
				for(int j=0;j<size;j++) {
					std::stringstream ss;
					ss << std::fixed << std::setprecision( 6 ) << (*data)[i][j];
					table->item(i,j)->setText(QString( ss.str().c_str() ));
				}
			}
		}
	};
	class WatchMat3Controller : public Controller {
	public:
		static const int size = 3;
		const char * title;
		QLabel * label;
		QTableWidget * table;
		glm::mat3 * data;

		WatchMat3Controller() {
			table = new QTableWidget(size,size) ;
			label = new QLabel();
		}

		inline void init(const char * name, glm::mat3 * toWatch) {
			title = name;
			data = toWatch;
			label->setText(name);
			update();
		}
		inline void update() {
			for(int i=0;i<size;i++) {
				for(int j=0;j<size;j++) {
					std::stringstream ss;
					ss << std::fixed << std::setprecision( 6 ) << (*data)[i][j];
					table->item(i,j)->setText(QString( ss.str().c_str() ));
				}
			}
		}
	};
}


DebugMenuManager::DebugMenuManager() {
	defaultTabName = "default";
	tabManager = new QTabWidget();
	defaultSliderGranularity = 100;
}

void DebugMenuManager::setDefaultTab(const char * tabname) {
	defaultTabName = tabname;
}
QVBoxLayout * DebugMenuManager::getTabLayout(const char * name) {
	name = name == nullptr ? defaultTabName : name;
	for (uint i = 0; i < tabs.size(); i++)
	{
		if(name == tabs[i].name) return tabs[i].layout;
	}
	QVBoxLayout * layout = new QVBoxLayout();
	QWidget * widg = new QWidget();
		
	widg -> setLayout(layout);

	int index = tabManager->addTab(widg,name);
	TabData toAdd = {name,layout,index};
	tabs.push_back( toAdd );
	return layout;
}


void DebugMenuManager::hide() { return tabManager->hide(); }
void DebugMenuManager::show() { return tabManager->show(); }
bool DebugMenuManager::isHidden() { return tabManager->isHidden(); }
QWidget * DebugMenuManager::getWidg() { return tabManager; };

void DebugMenuManager::setSliderGranularity(int valueToSet) {
	defaultSliderGranularity = valueToSet;
}

const char * DebugMenuManager::getActiveTab() {
	for (uint i = 0; i < tabs.size(); i++)
	{
		if(tabManager->currentIndex()== tabs[i].index) return tabs[i].name;
	}
	return nullptr;
}
//returns true if tab is active
bool DebugMenuManager::isActiveTab(const char * tabname) {
	return tabname == getActiveTab();
}

//returns false if tab not found
bool DebugMenuManager::setActiveTab(const char * tabname) {
	int index = -1;
	for (uint i = 0; i < tabs.size() || index < 0; i++)
	{
		if(tabname == tabs[i].name) index = tabs[i].index;
	}
	if(index>=0) {
		tabManager->setCurrentIndex(index);
		return true;
	}
	return false;
}


void DebugMenuManager::update() {
	for (uint i = 0; i < controllers.size(); i++) { controllers[i]->update(); }
}

void DebugMenuManager::watch(char * name, const char *& valueToWatch, char * tabName) {
	watchName(name,valueToWatch,tabName);
}
void DebugMenuManager::watch(char * name, float& toWatch, const char * tabName) {
	watchFloat(name, toWatch,tabName);
}
void DebugMenuManager::watch(char * name, int& toWatch, const char * tabName) {
	watchInt(name, toWatch,tabName);
}
void DebugMenuManager::watch(char * name, glm::vec3& toWatch, const char * tabName) {
	watchVector(name,toWatch,tabName);
}
void DebugMenuManager::watch(char * name, glm::vec4& toWatch, const char * tabName) {
	watchVector(name,toWatch,tabName);
}
void DebugMenuManager::edit (char * name, float& toWatch, float min, float max, bool doubleLink, const char * tabName) {
	slideFloat(name,toWatch,min,max,doubleLink,tabName);
}
void DebugMenuManager::edit (char * name, int&   toWatch, float min, float max, bool doubleLink, const char * tabName) {
	slideInt(name,toWatch,min,max,doubleLink,tabName);
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
void DebugMenuManager::edit (char * name, glm::vec4& toWatch, float min, float max, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,min,max,doubleLink,tabName);
}
void DebugMenuManager::edit (char * name, glm::vec4& toWatch, float rRange, float gRange, float bRange, float aRange, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,rRange,gRange,bRange,aRange,doubleLink,tabName);
}
void DebugMenuManager::edit (char * name, glm::vec4& toWatch, float rMin, float rMax, float gMin, float gMax, float bMin, float bMax, float aMin, float aMax, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,rMin,rMax,gMin,gMax,bMin,bMax,aMin,aMax,doubleLink,tabName);
}
void DebugMenuManager::watch(char * name, glm::mat3& toWatch, const char * tabName) {
	watchMat(name,toWatch,tabName);
}
void DebugMenuManager::watch(char * name, glm::mat4& toWatch, const char * tabName) {
	watchMat(name,toWatch,tabName);
}
void DebugMenuManager::edit (char * name, bool& toWatch, const char * tabName) {
	toggleBool(name,toWatch,tabName);
}
void DebugMenuManager::edit (char * name, fastdelegate::FastDelegate0<> callback, const char * tabName) {
	button(name,callback,tabName);
}

void DebugMenuManager::watchName(char * name, const char *& valueToWatch, char * tabName) {
	auto * toAdd = new DebugMenuControllers::CharPointerController();
	toAdd->init(name,&valueToWatch);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->label);
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchFloat (char * name, float& toWatch, const char * tabName)	  {
	DebugMenuControllers::WatchFloatController * toAdd = new DebugMenuControllers::WatchFloatController();
	toAdd->init(name,&toWatch);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchInt   (char * name, int&   toWatch, const char * tabName)	  {
	DebugMenuControllers::WatchIntController * toAdd = new DebugMenuControllers::WatchIntController();
	toAdd->init(name,&toWatch);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::slideFloat (char * name, float& toWatch, float min, float max, bool doubleLink, const char * tabName)	  {
	DebugMenuControllers::SlideFloatController * toAdd = new DebugMenuControllers::SlideFloatController();
	toAdd->init(name,&toWatch,min,max, doubleLink);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	toAdd->slider->setGranularity(defaultSliderGranularity);
	newRow->addWidget((toAdd->label));
	newRow->addWidget((toAdd->slider));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::slideInt   (char * name, int&   toWatch, float min, float max, bool doubleLink, const char * tabName)	  {
	DebugMenuControllers::SlideIntController * toAdd = new DebugMenuControllers::SlideIntController();
	toAdd->init(name,&toWatch,min,max, doubleLink);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	newRow->addWidget((toAdd->slider));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::toggleBool (char * name, bool& toWatch, const char * tabName)	  {
	DebugMenuControllers::BoolToggleController * toAdd = new DebugMenuControllers::BoolToggleController();
	toAdd->init(name,&toWatch);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->checkBox));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchVector(char * name, glm::vec3& toWatch, const char * tabName) {
	DebugMenuControllers::WatchVectorController * toAdd = new DebugMenuControllers::WatchVectorController();
	toAdd->init(name,&toWatch);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchVector(char * name, glm::vec4& toWatch, const char * tabName) {
	DebugMenuControllers::WatchVector4Controller * toAdd = new DebugMenuControllers::WatchVector4Controller();
	toAdd->init(name,&toWatch);
	controllers.push_back(toAdd);

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
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->label);
	newRow->addWidget(toAdd->xSlider);	toAdd->xSlider->setGranularity(defaultSliderGranularity);
	newRow->addWidget(toAdd->ySlider);	toAdd->ySlider->setGranularity(defaultSliderGranularity);
	newRow->addWidget(toAdd->zSlider);	toAdd->zSlider->setGranularity(defaultSliderGranularity);
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::slideVector(char * name, glm::vec4& toWatch, float min, float max, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,min,max,min,max,min,max,min,max,doubleLink,tabName);
}
void DebugMenuManager::slideVector(char * name, glm::vec4& toWatch, float rRange, float gRange, float bRange, float aRange, bool doubleLink, const char * tabName) {
	slideVector(name,toWatch,-rRange,rRange,-gRange,gRange,-bRange,bRange,-aRange,aRange,doubleLink,tabName);
}
void DebugMenuManager::slideVector(char * name, glm::vec4& toWatch, float rMin, float rMax, float gMin, float gMax, float bMin, float bMax, float aMin, float aMax, bool doubleLink, const char * tabName) {
	DebugMenuControllers::SlideVector4Controller * toAdd = new DebugMenuControllers::SlideVector4Controller();
	toAdd->init(name,&toWatch,rMin,rMax,gMin,gMax,bMin,bMax,aMin,aMax,doubleLink);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->label);
	newRow->addWidget(toAdd->rSlider);	toAdd->rSlider->setGranularity(defaultSliderGranularity);
	newRow->addWidget(toAdd->gSlider);	toAdd->gSlider->setGranularity(defaultSliderGranularity);
	newRow->addWidget(toAdd->bSlider);	toAdd->bSlider->setGranularity(defaultSliderGranularity);
	newRow->addWidget(toAdd->aSlider);	toAdd->aSlider->setGranularity(defaultSliderGranularity);
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchMat   (char * name, glm::mat3& toWatch, const char * tabName) {
	DebugMenuControllers::WatchMat3Controller * toAdd = new DebugMenuControllers::WatchMat3Controller();
	toAdd->init(name,&toWatch);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	newRow->addWidget((toAdd->table));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::watchMat   (char * name, glm::mat4& toWatch, const char * tabName) {
	DebugMenuControllers::WatchMat4Controller * toAdd = new DebugMenuControllers::WatchMat4Controller();
	toAdd->init(name,&toWatch);
	controllers.push_back(toAdd);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget((toAdd->label));
	newRow->addWidget((toAdd->table));
	getTabLayout(tabName)->addLayout(newRow);
}
void DebugMenuManager::button(char * name, fastdelegate::FastDelegate0<> callback, const char * tabName) {
	auto * toAdd = new ButtonInfo();
	toAdd->init(name,callback);

	QHBoxLayout * newRow = new QHBoxLayout();
	newRow->addWidget(toAdd->button);
	getTabLayout(tabName)->addLayout(newRow);
}
