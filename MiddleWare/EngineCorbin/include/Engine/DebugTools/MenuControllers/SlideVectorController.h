#pragma once

#include <Qt/qlabel.h>
#include <Engine/Tools/QT/LinkedSlider.h>
#include <glm/glm.hpp>
#include <ExportHeader.h>

namespace DebugMenuControllers {
	struct ENGINE_SHARED SlideVectorController {
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
	};
}