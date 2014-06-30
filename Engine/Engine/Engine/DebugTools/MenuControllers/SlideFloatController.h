#pragma once

#include <Qt/qlabel.h>
#include <Engine/Tools/QT/LinkedSlider.h>
#include <ExportHeader.h>

namespace DebugMenuControllers {
	struct ENGINE_SHARED SlideFloatController {
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
	};
}